/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_LOCATION_HPP
#define LASTFM_LOCATION_HPP

#include <lastfmpp/lastfmpp.hpp>

namespace lastfmpp {

struct LASTFM_EXPORT location {
    location() = default;

    std::string_view street() const;
    void street(std::string_view street);

    std::string_view city() const;
    void city(std::string_view city);

    std::string_view country() const;
    void country(std::string_view country);

    std::string_view post_code() const;
    void post_code(std::string_view post_code);

    // api methods

private:
    std::string m_street;
    std::string m_city;
    std::string m_country;
    std::string m_post_code;
};

using geo = location;

} // namespace lastfmpp

#endif // LASTFM_LOCATION_HPP
