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

#ifndef LASTFM_DESERIALISE_EVENT
#define LASTFM_DESERIALISE_EVENT

#include <jbson/element.hpp>

#include <lastfmpp/event.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_artist.hpp>
#include <lastfmpp/detail/deserialise_image.hpp>
#include <lastfmpp/detail/deserialise_venue.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& event_elem, event& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(event_elem);
    for(auto&& elem : doc) {
        if(elem.name() == "id") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.id({str.data(), str.size()});
        } else if(elem.name() == "title") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.name({str.data(), str.size()});
        } else if(elem.name() == "url") {
            var.url(jbson::get<uri_t>(elem));
        } else if(elem.name() == "attendance") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.attendance(std::strtol(str.data(), nullptr, 10));
        } else if(elem.name() == "description") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.description(str);
        } else if(elem.name() == "startDate") {
            var.start_date(jbson::get<date_t>(elem));
        } else if(elem.name() == "venue") {
            var.venue(jbson::get<venue>(elem));
        } else if(elem.name() == "artists") {
            if(elem.type() == jbson::element_type::document_element) {
                for(auto&& e : jbson::get<jbson::element_type::document_element>(elem))
                    if(e.name() == "artist")
                        var.artists(jbson::get<std::vector<artist>>(e));
            } else {
                var.artists(jbson::get<std::vector<artist>>(elem));
            }
        } else if(elem.name() == "image") {
            var.images(jbson::get<std::vector<image>>(elem));
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_EVENT

