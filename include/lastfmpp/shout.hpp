/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_SHOUT_HPP
#define LASTFM_SHOUT_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/date.hpp>

namespace lastfmpp {

class service;

struct LASTFM_EXPORT shout {
    shout() = default;

    std::string_view author() const;
    void author(std::string_view);

    std::string_view body() const;
    void body(std::string_view);

    time_point date() const;
    void date(time_point);

  private:
    std::string m_author;
    std::string m_body;
    time_point m_date;
};

} // namespace lastfm

#endif // LASTFM_SHOUT_HPP
