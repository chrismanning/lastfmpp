/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <openssl/md5.h>

#include <boost/hana/ext/std.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptors.hpp>

#include <jbson/json_reader.hpp>

#include <lastfmpp/detail/service_impl.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/error.hpp>

namespace lastfmpp {

namespace hana = boost::hana;

namespace {
struct to_doc_impl {
    jbson::document operator()(std::string body) const {
        auto doc = jbson::read_json(body);
        detail::check_error(doc);
        return doc;
    }
};
}
static constexpr to_doc_impl to_doc{};

service::impl::impl(std::experimental::string_view api_key, std::experimental::string_view shared_secret,
                    std::experimental::optional<std::experimental::string_view> session_key)
    : cas_client(uri_t{base_url.to_string()}), api_key(api_key), shared_secret(shared_secret) {
    assert(!api_key.empty());
    assert(!shared_secret.empty());
    if(session_key) {
        this->session_key = session_key->to_string();
    }
}

pplx::task<jbson::document> service::impl::get(std::experimental::string_view method, params_t params) {
    auto query = uri_builder().set_query(make_query(make_params(method, std::move(params), false))).to_string();
    return cas_client.request(web::http::methods::GET, query).then(response_to_u8).then(to_doc);
}

pplx::task<jbson::document> service::impl::post_session(std::experimental::string_view method, params_t params) {
    params.emplace_back("sk", get_session_key());
    return post(method, std::move(params));
}

pplx::task<jbson::document> service::impl::post(std::experimental::string_view method, params_t params) {
    auto query = make_query(make_params(method, std::move(params), true));
    return cas_client.request(web::http::methods::POST, "", query, U("application/x-www-form-urlencoded"))
        .then(response_to_u8)
        .then(to_doc);
}

encoded_params_t service::impl::make_params(std::experimental::string_view method, params_t params,
                                            bool needs_signature) {
    params.emplace_back("api_key", api_key);
    params.emplace_back("method", method.to_string());

    auto encoded_params = transform_copy(std::move(params), [](auto&& param) {
        return hana::transform(std::forward<decltype(param)>(param), [](auto&& query) {
            return uri_t::encode_uri(to_string_t(std::forward<decltype(query)>(query)), uri_t::components::query);
        });
    });

    boost::sort(encoded_params, [](auto&& a, auto&& b) { return std::get<0>(a) < std::get<0>(b); });

    if(needs_signature) {
        encoded_params.emplace_back("api_sig", sign(encoded_params));
    }

    return encoded_params;
}

utility::string_t service::impl::make_query(encoded_params_t params) {
    params.emplace_back(U("format"), U("json"));
    auto joined_pairs = boost::adaptors::transform(params, [](auto&& param) {
        return hana::unpack(std::forward<decltype(param)>(param), [](auto&& a, auto&& b) { return a + U("=") + b; });
    });
    return boost::algorithm::join(joined_pairs, "&");
}

utility::string_t service::impl::sign(params_t params) {
    auto sig = flatten((params.emplace_back(shared_secret, ""), params));

    std::array<uint8_t, MD5_DIGEST_LENGTH> sigp;
    MD5(reinterpret_cast<const uint8_t*>(sig.c_str()), sig.length(), sigp.data());

    utility::string_t hex_sig;
    hex_sig.reserve(sigp.size() * 2);
    boost::algorithm::hex(sigp, std::back_inserter(hex_sig));
    assert(hex_sig.size() == MD5_DIGEST_LENGTH * 2);

    return hex_sig;
}

std::string service::impl::flatten(const params_t& params) {
    return boost::accumulate(params, std::string{}, [](auto&& out, auto&& param) -> decltype(auto) {
        out += std::get<0>(param) + std::get<1>(param);
        return std::move(out);
    });
}

void service::impl::set_session_key(std::experimental::string_view sk) {
    std::lock_guard<decltype(session_mu)> l(session_mu);
    session_key = sk.to_string();
}

std::string service::impl::get_session_key() const {
    std::shared_lock<std::remove_cv_t<decltype(session_mu)>> l(session_mu);
    return session_key;
}

} // namespace lastfmpp
