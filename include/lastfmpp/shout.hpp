/**************************************************************************
**  Copyright (C) 2015 Christian Manning
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef LASTFM_SHOUT_HPP
#define LASTFM_SHOUT_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/date.hpp>

namespace lastfmpp {

class service;

struct LASTFM_EXPORT shout {
    explicit shout() = default;

    std::string_view author() const;
    void author(std::string_view);

    std::string_view body() const;
    void body(std::string_view);

    date_t date() const;
    void date(date_t);

  private:
    std::string m_author;
    std::string m_body;
    date_t m_date;
};

} // namespace lastfm

#endif // LASTFM_SHOUT_HPP
