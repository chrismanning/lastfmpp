/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_VENUE_HPP
#define LASTFM_VENUE_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/image.hpp>
#include <lastfmpp/location.hpp>

namespace lastfmpp {

class service;
struct image;
struct event;

struct LASTFM_EXPORT venue {
    venue() = default;

    std::experimental::string_view id() const;
    void id(std::experimental::string_view id);

    std::experimental::string_view name() const;
    void name(std::experimental::string_view name);

    const uri_t& url() const;
    void url(uri_t url);

    const uri_t& website() const;
    void website(uri_t website);

    const std::vector<image>& images() const;
    void images(std::vector<image> images);

    const location& location() const;
    void location(struct location location);

    // api methods

    static pplx::task<std::vector<event>> get_events(service&, std::experimental::string_view venue_id,
                                                     bool festivals_only = false);
    pplx::task<std::vector<event>> get_events(service&, bool festivals_only = false) const;

    static pplx::task<std::vector<event>>
    get_past_events(service&, std::experimental::string_view venue_id, bool festivals_only = false,
                    std::experimental::optional<int> limit = std::experimental::nullopt,
                    std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<event>>
    get_past_events(service&, bool festivals_only = false,
                    std::experimental::optional<int> limit = std::experimental::nullopt,
                    std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<venue>>
    search(service&, std::experimental::string_view venue_id,
           std::experimental::optional<std::experimental::string_view> country = std::experimental::nullopt,
           std::experimental::optional<int> limit = std::experimental::nullopt,
           std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<venue>>
    search(service&, std::experimental::optional<std::experimental::string_view> country = std::experimental::nullopt,
           std::experimental::optional<int> limit = std::experimental::nullopt,
           std::experimental::optional<int> page = std::experimental::nullopt) const;

  private:
    std::string m_id;
    std::string m_name;
    uri_t m_url;
    uri_t m_website;
    std::vector<image> m_images;
    struct location m_location;
};

} // namespace lastfm

#endif // LASTFM_VENUE_HPP
