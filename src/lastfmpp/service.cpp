/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <memory>
#include <shared_mutex>

#include <openssl/md5.h>

#include <cpprest/http_client.h>

#include <boost/hana/ext/std.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptors.hpp>

#include <jbson/document.hpp>
#include <jbson/json_reader.hpp>

#include <lastfmpp/service.hpp>
#include <lastfmpp/user.hpp>
#include <lastfmpp/detail/error.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/params.hpp>

namespace lastfmpp {

namespace hana = boost::hana;

static constexpr auto base_url = U("https://ws.audioscrobbler.com/2.0/"_sv);

namespace {
struct {
    pplx::task<std::string> operator()(web::http::http_response response) const {
        return response.extract_utf8string(true);
    }
} response_to_u8;
}
using utility::conversions::to_string_t;

using encoded_params_t = std::vector<std::tuple<utility::string_t, utility::string_t>>;

struct service::impl {
    impl(std::string_view api_key, std::string_view shared_secret)
        : cas_client(uri_t{base_url.to_string()}), api_key(api_key), shared_secret(shared_secret) {
        assert(!api_key.empty());
        assert(!shared_secret.empty());
    }

    pplx::task<std::string> get(std::string_view method, params_t params) {
        auto query = uri_builder().set_query(make_query(make_params(method, std::move(params), false))).to_string();
        return cas_client.request(web::http::methods::GET, query).then(response_to_u8);
    }

    pplx::task<std::string> session_post(std::string_view method, params_t params) {
        params.emplace_back("sk", get_session_key());
        return post(method, std::move(params));
    }

    pplx::task<std::string> post(std::string_view method, params_t params) {
        auto query = make_query(make_params(method, std::move(params), true));
        return cas_client.request(web::http::methods::POST, "", query, U("application/x-www-form-urlencoded"))
            .then(response_to_u8);
    }

    encoded_params_t make_params(std::string_view method, params_t params, bool needs_signature) {
        params.emplace_back("api_key", api_key);
        params.emplace_back("method", method);

        auto encoded_params = transform_copy(params, [](auto&& param) {
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

    utility::string_t make_query(encoded_params_t params) {
        params.emplace_back(U("format"), U("json"));
        auto joined_pairs = boost::adaptors::transform(params, [](auto&& param) {
            return hana::unpack(std::forward<decltype(param)>(param),
                                [](auto&& a, auto&& b) { return a + U("=") + b; });
        });
        return boost::algorithm::join(joined_pairs, "&");
    }

    utility::string_t sign(params_t params) {
        auto sig = flatten((params.emplace_back(shared_secret, ""), params));

        std::array<uint8_t, MD5_DIGEST_LENGTH> sigp;
        MD5(reinterpret_cast<const uint8_t*>(sig.c_str()), sig.length(), sigp.data());

        utility::string_t hex_sig;
        hex_sig.reserve(sigp.size() * 2);
        boost::algorithm::hex(sigp, std::back_inserter(hex_sig));
        assert(hex_sig.size() == MD5_DIGEST_LENGTH * 2);

        return hex_sig;
    }

    static std::string flatten(const params_t& params) {
        return boost::accumulate(params, std::string{}, [](auto&& out, auto&& param) -> decltype(auto) {
            out += std::get<0>(param) + std::get<1>(param);
            return std::move(out);
        });
    }

    void set_session_key(std::string_view sk) {
        std::lock_guard<decltype(session_mu)> l(session_mu);
        session_key = sk.to_string();
    }

    std::string get_session_key() const {
        std::shared_lock<std::remove_cv_t<decltype(session_mu)>> l(session_mu);
        return session_key;
    }

    web::http::client::http_client cas_client;

    const std::string api_key;
    const std::string shared_secret;
    mutable std::shared_timed_mutex session_mu;
    user user;

  private:
    std::string session_key;
};

service::service(std::string_view api_key, std::string_view shared_secret)
    : pimpl(std::make_unique<impl>(api_key, shared_secret)) {
}

service::~service() {
}

std::string_view service::api_key() const {
    return pimpl->api_key;
}

std::string_view service::shared_secret() const {
    return pimpl->shared_secret;
}

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

pplx::task<jbson::document> service::get(std::string_view method, params_t params) {
    return pimpl->get(method, std::move(params)).then(to_doc);
}

pplx::task<jbson::document> service::post(std::string_view method, params_t params) {
    return pimpl->post(method, std::move(params)).then(to_doc);
}

pplx::task<jbson::document> service::post_session(std::string_view method, params_t params) {
    return pimpl->session_post(method, std::move(params)).then(to_doc);
}

pplx::task<std::string> service::get_mobile_session(std::string_view username, std::string_view password) {
    return post("auth.getmobilesession",
                detail::make_params(std::make_pair("username", username), std::make_pair("password", password)),
                transform_select<std::string>("session.key"))
        .then([this](std::string session) {
            pimpl->set_session_key(session);
            return session;
        });
}

} // namespace lastfm
