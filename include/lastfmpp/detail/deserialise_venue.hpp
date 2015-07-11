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

#ifndef LASTFM_DESERIALISE_VENUE
#define LASTFM_DESERIALISE_VENUE

#include <jbson/element.hpp>

#include <lastfmpp/venue.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_image.hpp>
#include <lastfmpp/detail/deserialise_location.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& venue_elem, venue& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(venue_elem);
    for(auto&& elem : doc) {
        if(elem.name() == "id") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.id({str.data(), str.size()});
        } else if(elem.name() == "name") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.name({str.data(), str.size()});
        } else if(elem.name() == "url") {
            var.url(jbson::get<uri_t>(elem));
        } else if(elem.name() == "website") {
            var.website(jbson::get<uri_t>(elem));
        } else if(elem.name() == "image") {
            var.images(jbson::get<std::vector<image>>(elem));
        } else if(elem.name() == "location") {
            var.location(jbson::get<location>(elem));
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_VENUE

