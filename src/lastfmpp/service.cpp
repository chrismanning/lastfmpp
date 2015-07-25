/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <memory>

#include <openssl/md5.h>

#include <cpprest/http_client.h>

#include <boost/hana/ext/std.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptor/formatted.hpp>

#include <jbson/document.hpp>
#include <jbson/json_reader.hpp>

#include <lastfmpp/service.hpp>
#include <lastfmpp/user.hpp>
#include <lastfmpp/detail/error.hpp>

namespace lastfmpp {

namespace hana = boost::hana;

static constexpr auto base_url = U("http://ws.audioscrobbler.com/2.0/"_sv);

namespace {
struct convert_to_casablanca_string_impl {
    template <typename S> auto operator()(S&& in) const -> decltype(in.to_string(), utility::string_t{}) {
        return utility::conversions::to_string_t(in.to_string());
    }
    template <typename S> auto operator()(S&& in) const -> decltype(utility::conversions::to_string_t(in)) {
        return utility::conversions::to_string_t(std::forward<S>(in));
    }
};
}
static constexpr convert_to_casablanca_string_impl convert_to_casablanca_string{};

struct service::impl {
    impl(std::string_view api_key, std::string_view shared_secret)
        : cas_client(uri_t{base_url.to_string()}), api_key(api_key), shared_secret(shared_secret) {
        assert(!api_key.empty());
        assert(!shared_secret.empty());
    }

    pplx::task<std::string> get(std::string_view method, params_t params) {
        uri_builder uri_build;

        uri_build.append_query(U("method"), convert_to_casablanca_string(method));
        for(auto&& member : params) {
            hana::unpack(hana::transform(std::move(member), convert_to_casablanca_string),
                         [&](auto&& a, auto&& b) { uri_build.append_query(std::move(a), std::move(b), true); });
        }
        uri_build.append_query(U("format"), U("json"));
        uri_build.append_query(U("api_key"), convert_to_casablanca_string(api_key));

        return cas_client.request(web::http::methods::GET, uri_build.to_string())
            .then([](web::http::http_response response) { return response.extract_utf8string(true); });
    }

    pplx::task<std::string> post(std::string_view method, params_t params) {

    }

    params_t sign(std::string_view method, params_t params) {
        params.emplace_back("api_key", api_key);
        params.emplace_back("method", method);
        using std::get;
        boost::sort(params, [](auto&& a, auto&& b) { return get<0>(a) < get<1>(b); });

        auto sig = join(flatten(params));

        std::array<uint8_t, MD5_DIGEST_LENGTH> sigp;
        MD5(reinterpret_cast<const uint8_t*>(sig.c_str()), sig.length(), sigp.data());

        std::string hex_sig;
        hex_sig.reserve(sigp.size() * 2);
        boost::algorithm::hex(sigp, std::back_inserter(hex_sig));
        assert(hex_sig.size() == MD5_DIGEST_LENGTH * 2);

        return {{"api_key", api_key}, {"api_sig", hex_sig}, {"sk", session_key}, {"format", "json"}};
    }

    std::string join(std::vector<std::string_view> params) {
        std::stringstream ss;
        ss << boost::adaptors::format(params, "", "", "");
        ss << shared_secret;
        return ss.str();
    }

    static std::vector<std::string_view> flatten(const params_t& params) {
        return boost::accumulate(params, std::vector<std::string_view>{},
                                 [](auto&& out, auto&& param) -> decltype(auto) {
            out.insert(out.end(), {std::get<0>(param), std::get<1>(param)});
            return std::forward<decltype(out)>(out);
        });
    }

    web::http::client::http_client cas_client;

    const std::string api_key;
    const std::string shared_secret;
    std::string session_key;
    user user;
    friend class service;
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

pplx::task<jbson::document> service::get(std::string_view method, params_t params) {
    return pimpl->get(method, std::move(params))
        .then([](std::string body) {
            auto doc = jbson::read_json(body);
            detail::check_error(doc);
            return doc;
        });
}

} // namespace lastfm
