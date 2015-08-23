/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
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
    event() = default;

    std::string_view id() const;
    void id(std::string_view id);

    std::string_view name() const;
    void name(std::string_view name);

    const std::vector<artist>& artists() const;
    void artists(std::vector<artist> artists);

    const venue& venue() const;
    void venue(struct venue venue);

    time_point start_date() const;
    void start_date(time_point start_date);

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
    time_point m_start_date;
    std::string m_description;
    std::vector<image> m_images;
    int m_attendance = 0;
    uri_t m_url;
};

} // namespace lastfm

#endif // LASTFM_EVENT_HPP
