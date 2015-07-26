/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFMPP_SERVICE_ACCESS
#define LASTFMPP_SERVICE_ACCESS

#include <lastfmpp/service.hpp>
#include <lastfmpp/detail/service_impl.hpp>

namespace lastfmpp::detail {

    struct service_access {
        template <typename... Args> static auto get(service& serv, Args&&... args) {
            return serv.pimpl->get(std::forward<Args>(args)...);
        }

        template <typename... Args> static auto post(service& serv, Args&&... args) {
            return serv.pimpl->post(std::forward<Args>(args)...);
        }

        template <typename... Args> static auto post_session(service& serv, Args&&... args) {
            return serv.pimpl->post_session(std::forward<Args>(args)...);
        }
    };
}

#endif // LASTFMPP_SERVICE_ACCESS
