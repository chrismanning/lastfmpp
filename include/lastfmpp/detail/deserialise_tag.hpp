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

#ifndef LASTFM_DESERIALISE_TAG
#define LASTFM_DESERIALISE_TAG

#include <jbson/element.hpp>

#include <lastfmpp/tag.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_wiki.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& tag_elem, tag& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(tag_elem);
    for(auto&& elem : doc) {
        if(elem.name() == "name") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.name({str.data(), str.size()});
        } else if(elem.name() == "url") {
            var.url(jbson::get<uri_t>(elem));
        } else if(elem.name() == "reach") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.reach(std::strtol(str.data(), nullptr, 10));
        } else if(elem.name() == "taggings") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.taggings(std::strtol(str.data(), nullptr, 10));
        } else if(elem.name() == "streamable") {
            var.streamable(jbson::get<jbson::element_type::string_element>(elem) == "1");
        } else if(elem.name() == "wiki") {
            var.wiki(jbson::get<wiki>(elem));
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_TAG

