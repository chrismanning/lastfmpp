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

#ifndef LASTFM_DESERIALISE_ARTIST_HPP
#define LASTFM_DESERIALISE_ARTIST_HPP

#include <jbson/element.hpp>

#include <lastfmpp/artist.hpp>
#include <lastfmpp/detail/deserialise_tag.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_image.hpp>
#include <lastfmpp/detail/deserialise_mbid.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& artist_elem, artist& var) {
    if(artist_elem.type() == jbson::element_type::string_element) {
        var.name(jbson::get<jbson::element_type::string_element>(artist_elem));
        return;
    }
    auto doc = jbson::get<jbson::element_type::document_element>(artist_elem);
    for(auto&& elem : doc) {
        if(elem.name() == "name") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.name({str.data(), str.size()});
        } else if(elem.name() == "url") {
            var.url(jbson::get<web::uri>(elem));
        } else if(elem.name() == "listeners") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.listeners(std::strtol(str.data(), nullptr, 10));
        } else if(elem.name() == "plays") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.plays(std::strtol(str.data(), nullptr, 10));
        } else if(elem.name() == "streamable") {
            var.streamable(jbson::get<jbson::element_type::string_element>(elem) == "1");
        } else if(elem.name() == "bio") {
            var.wiki(jbson::get<wiki>(elem));
        } else if(elem.name() == "similar") {
            if(elem.type() == jbson::element_type::document_element) {
                for(auto&& e : jbson::get<jbson::element_type::document_element>(elem))
                    if(e.name() == "artist")
                        var.similar(jbson::get<std::vector<artist>>(e));
            } else {
                var.similar(jbson::get<std::vector<artist>>(elem));
            }
        } else if(elem.name() == "tags" || elem.name() == "toptags") {
            if(elem.type() == jbson::element_type::document_element) {
                for(auto&& e : jbson::get<jbson::element_type::document_element>(elem))
                    if(e.name() == "tag")
                        var.top_tags(jbson::get<std::vector<tag>>(e));
            } else {
                var.top_tags(jbson::get<std::vector<tag>>(elem));
            }
        } else if(elem.name() == "image") {
            var.images(jbson::get<std::vector<image>>(elem));
        } else if(elem.name() == "mbid") {
            var.mbid(jbson::get<mbid_t>(elem));
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_ARTIST_HPP
