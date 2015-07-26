/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFMPP_SERVICE_IMPL
#define LASTFMPP_SERVICE_IMPL

#include <shared_mutex>

#include <cpprest/http_client.h>

#include <jbson/document.hpp>

#include <lastfmpp/service.hpp>
#include <lastfmpp/uri.hpp>
#include <lastfmpp/user.hpp>

namespace lastfmpp {

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
    impl(std::string_view api_key, std::string_view shared_secret);

    pplx::task<jbson::document> get(std::string_view method, params_t params);
    template <typename TransformerT, typename ReturnT = std::result_of_t<TransformerT(jbson::document)>>
    pplx::task<ReturnT> get(std::string_view method, params_t params, TransformerT&& transform);

    pplx::task<jbson::document> post_session(std::string_view method, params_t params);

    template <typename TransformerT, typename ReturnT = std::result_of_t<TransformerT(jbson::document)>>
    pplx::task<ReturnT> post_session(std::string_view method, params_t params, TransformerT&& transform);

    pplx::task<jbson::document> post(std::string_view method, params_t params);

    template <typename TransformerT, typename ReturnT = std::result_of_t<TransformerT(jbson::document)>>
    pplx::task<ReturnT> post(std::string_view method, params_t params, TransformerT&& transform);

    encoded_params_t make_params(std::string_view method, params_t params, bool needs_signature);

    utility::string_t make_query(encoded_params_t params);

    utility::string_t sign(params_t params);

    static std::string flatten(const params_t& params);

    void set_session_key(std::string_view sk);

    std::string get_session_key() const;

    web::http::client::http_client cas_client;

    const std::string api_key;
    const std::string shared_secret;
    mutable std::shared_timed_mutex session_mu;
    user user;

  private:
    std::string session_key;
};

template <typename TransformerT, typename ReturnT>
pplx::task<ReturnT> service::impl::get(std::string_view method, params_t params, TransformerT&& transform) {
    return get(method, std::move(params)).then(transform);
}

template <typename TransformerT, typename ReturnT>
pplx::task<ReturnT> service::impl::post(std::string_view method, params_t params, TransformerT&& transform) {
    return post(method, std::move(params)).then(transform);
}

template <typename TransformerT, typename ReturnT>
pplx::task<ReturnT> service::impl::post_session(std::string_view method, params_t params, TransformerT&& transform) {
    return post_session(method, std::move(params)).then(transform);
}

} // namespace lastfmpp

#endif // LASTFMPP_SERVICE_IMPL
