/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
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
