/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_SERVICE_HPP
#define LASTFM_SERVICE_HPP

#include <string>
#include <memory>
#include <vector>
#include <cstdlib>

#include <pplx/pplxtasks.h>

#include <jbson/document.hpp>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/params.hpp>

namespace lastfmpp {

namespace detail {
struct service_access;
}

class LASTFM_EXPORT service {
  public:
    explicit service(
        std::experimental::string_view api_key, std::experimental::string_view shared_secret,
        std::experimental::optional<std::experimental::string_view> session_key = std::experimental::nullopt);

    ~service();

    pplx::task<std::string> get_mobile_session(std::experimental::string_view username,
                                               std::experimental::string_view password);

  private:
    struct impl;
    std::unique_ptr<impl> pimpl;
    friend struct detail::service_access;
};

} // namespace lastfm

#endif // LASTFM_SERVICE_HPP
