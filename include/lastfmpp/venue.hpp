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
    explicit venue() = default;

    std::string_view id() const;
    void id(std::string_view id);

    std::string_view name() const;
    void name(std::string_view name);

    const uri_t& url() const;
    void url(uri_t url);

    const uri_t& website() const;
    void website(uri_t website);

    const std::vector<image>& images() const;
    void images(std::vector<image> images);

    const location& location() const;
    void location(struct location location);

    // api methods

    static pplx::task<std::vector<event>> get_events(service&, std::string_view venue_id, bool festivals_only = false);
    pplx::task<std::vector<event>> get_events(service&, bool festivals_only = false) const;

    static pplx::task<std::vector<event>> get_past_events(service&, std::string_view venue_id,
                                                          bool festivals_only = false,
                                                          std::optional<int> limit = std::nullopt,
                                                          std::optional<int> page = std::nullopt);
    pplx::task<std::vector<event>> get_past_events(service&, bool festivals_only = false,
                                                   std::optional<int> limit = std::nullopt,
                                                   std::optional<int> page = std::nullopt) const;

    static pplx::task<std::vector<venue>> search(service&, std::string_view venue_id,
                                                 std::optional<std::string_view> country = std::nullopt,
                                                 std::optional<int> limit = std::nullopt,
                                                 std::optional<int> page = std::nullopt);
    pplx::task<std::vector<venue>> search(service&, std::optional<std::string_view> country = std::nullopt,
                                          std::optional<int> limit = std::nullopt,
                                          std::optional<int> page = std::nullopt) const;

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
