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

#ifndef LASTFM_DESERIALISE_IMAGE
#define LASTFM_DESERIALISE_IMAGE

#include <jbson/element.hpp>

#include <lastfmpp/image.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& elem, image& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(elem);
    for(auto&& elem : doc) {
        if(elem.name() == "#text") {
            var.uri(jbson::get<uri_t>(elem));
        } else if(elem.name() == "size") {
            var.size(jbson::get<image_size>(elem));
        }
    }
}

template <typename Container> void value_get(const jbson::basic_element<Container>& elem, image_size& var) {
    static const std::unordered_map<std::string_view, image_size> map = {{"small"_sv, image_size::small},
                                                                         {"medium"_sv, image_size::medium},
                                                                         {"large"_sv, image_size::large},
                                                                         {"extralarge"_sv, image_size::extralarge},
                                                                         {"mega"_sv, image_size::mega}};
    auto str = jbson::get<jbson::element_type::string_element>(elem);
    var = map.at(str);
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_IMAGE

