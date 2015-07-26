/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/venue.hpp>
#include <lastfmpp/detail/service_access.hpp>
#include <lastfmpp/event.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/detail/params.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_venue.hpp>
#include <lastfmpp/detail/deserialise_event.hpp>

namespace lastfmpp {

std::string_view venue::id() const {
    return m_id;
}

void venue::id(std::string_view id) {
    m_id = id.to_string();
}

std::string_view venue::name() const {
    return m_name;
}

void venue::name(std::string_view name) {
    m_name = name.to_string();
}

const uri_t& venue::url() const {
    return m_url;
}

void venue::url(uri_t url) {
    m_url = std::move(url);
}

const uri_t& venue::website() const {
    return m_website;
}

void venue::website(uri_t website) {
    m_website = std::move(website);
}

const std::vector<image>& venue::images() const {
    return m_images;
}

void venue::images(std::vector<image> images) {
    m_images = std::move(images);
}

const location& venue::location() const {
    return m_location;
}

void venue::location(struct location location) {
    m_location = std::move(location);
}

pplx::task<std::vector<event>> venue::get_events(service& serv, std::string_view venue_id, bool festivals_only) {
    return detail::service_access::get(
        serv, "venue.getevents",
        detail::make_params(std::make_pair("id", venue_id), std::make_pair("festivalsonly", festivals_only)),
        transform_select<std::vector<event>>("events.event.*"));
}

pplx::task<std::vector<event>> venue::get_events(service& serv, bool festivals_only) const {
    return get_events(serv, m_id, festivals_only);
}

pplx::task<std::vector<event>> venue::get_past_events(service& serv, std::string_view venue_id, bool festivals_only,
                                                      std::optional<int> limit, std::optional<int> page) {
    return detail::service_access::get(
        serv, "venue.getevents",
        detail::make_params(std::make_pair("id", venue_id), std::make_pair("festivalsonly", festivals_only),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<event>>("events.event.*"));
}

pplx::task<std::vector<event>> venue::get_past_events(service& serv, bool festivals_only, std::optional<int> limit,
                                                      std::optional<int> page) const {
    return get_past_events(serv, m_id, festivals_only, limit, page);
}

pplx::task<std::vector<venue>> venue::search(service& serv, std::string_view venue_id,
                                             std::optional<std::string_view> country, std::optional<int> limit,
                                             std::optional<int> page) {
    return detail::service_access::get(
        serv, "venue.search", detail::make_params(std::make_pair("id", venue_id), std::make_pair("country", country),
                                                  std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<venue>>("results.venuematches.track.*"));
}

pplx::task<std::vector<venue>> venue::search(service& serv, std::optional<std::string_view> country,
                                             std::optional<int> limit, std::optional<int> page) const {
    return search(serv, m_id, country, limit, page);
}

} // namespace lastfm
