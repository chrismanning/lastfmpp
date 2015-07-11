/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/shout.hpp>

namespace lastfmpp {

std::string_view shout::author() const {
    return m_author;
}

void shout::author(std::string_view author) {
    m_author = author.to_string();
}

std::string_view shout::body() const {
    return m_body;
}

void shout::body(std::string_view body) {
    m_body = body.to_string();
}

date_t shout::date() const {
    return m_date;
}

void shout::date(date_t date) {
    m_date = date;
}

} // namespace lastfm
