/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <memory>

#include <jbson/document.hpp>
#include <jbson/json_reader.hpp>

#include <lastfmpp/detail/service_access.hpp>
#include <lastfmpp/detail/service_impl.hpp>
#include <lastfmpp/user.hpp>
#include <lastfmpp/detail/error.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/params.hpp>

namespace lastfmpp {

service::service(std::string_view api_key, std::string_view shared_secret, std::optional<std::string_view> session_key)
    : pimpl(std::make_unique<impl>(api_key, shared_secret, session_key)) {
}

service::~service() {
}

pplx::task<std::string> service::get_mobile_session(std::string_view username, std::string_view password) {
    return pimpl->post("auth.getmobilesession",
                       detail::make_params(std::make_pair("username", username), std::make_pair("password", password)),
                       transform_select<std::string>("session.key"))
        .then([this](std::string session) {
            pimpl->set_session_key(session);
            return session;
        });
}

} // namespace lastfm
