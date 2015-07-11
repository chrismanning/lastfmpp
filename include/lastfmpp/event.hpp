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

#ifndef LASTFM_EVENT_HPP
#define LASTFM_EVENT_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/venue.hpp>
#include <lastfmpp/image.hpp>
#include <lastfmpp/date.hpp>

namespace lastfmpp {

struct artist;

struct LASTFM_EXPORT event {
    explicit event() = default;

    std::string_view id() const;
    void id(std::string_view id);

    std::string_view name() const;
    void name(std::string_view name);

    const std::vector<artist>& artists() const;
    void artists(std::vector<artist> artists);

    const venue& venue() const;
    void venue(struct venue venue);

    date_t start_date() const;
    void start_date(date_t start_date);

    std::string_view description() const;
    void description(std::string_view description);

    const std::vector<image>& images() const;
    void images(std::vector<image> images);

    int attendance() const;
    void attendance(int attendance);

    const uri_t& url() const;
    void url(uri_t url);

  private:
    std::string m_id;
    std::string m_name;
    std::vector<artist> m_artists;
    struct venue m_venue;
    date_t m_start_date;
    std::string m_description;
    std::vector<image> m_images;
    int m_attendance = 0;
    uri_t m_url;
};

} // namespace lastfm

#endif // LASTFM_EVENT_HPP
