/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/location.hpp>

namespace lastfmpp {

std::string_view location::street() const {
    return m_street;
}

void location::street(std::string_view street) {
    m_street = street.to_string();
}

std::string_view location::city() const {
    return m_city;
}

void location::city(std::string_view city) {
    m_city = city.to_string();
}

std::string_view location::country() const {
    return m_country;
}

void location::country(std::string_view country) {
    m_country = country.to_string();
}

std::string_view location::post_code() const {
    return m_post_code;
}

void location::post_code(std::string_view post_code) {
    m_post_code = post_code.to_string();
}

} // namespace lastfmpp
