/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/event.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/detail/params.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/deserialise_event.hpp>

namespace lastfmpp {

std::experimental::string_view event::id() const {
    return m_id;
}

void event::id(std::experimental::string_view id) {
    m_id = id.to_string();
}

std::experimental::string_view event::name() const {
    return m_name;
}

void event::name(std::experimental::string_view name) {
    m_name = name.to_string();
}

const std::vector<artist>& event::artists() const {
    return m_artists;
}

void event::artists(std::vector<artist> artists) {
    m_artists = std::move(artists);
}

const venue& event::venue() const {
    return m_venue;
}

void event::venue(struct venue venue) {
    m_venue = std::move(venue);
}

time_point event::start_date() const {
    return m_start_date;
}

void event::start_date(time_point start_date) {
    m_start_date = start_date;
}

std::experimental::string_view event::description() const {
    return m_description;
}

void event::description(std::experimental::string_view description) {
    m_description = description.to_string();
}

const std::vector<image>& event::images() const {
    return m_images;
}

void event::images(std::vector<image> images) {
    m_images = std::move(images);
}

int event::attendance() const {
    return m_attendance;
}

void event::attendance(int attendance) {
    m_attendance = attendance;
}

const uri_t& event::url() const {
    return m_url;
}

void event::url(uri_t url) {
    m_url = std::move(url);
}

} // namespace lastfm
