/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_LOCATION
#define LASTFM_DESERIALISE_LOCATION

#include <jbson/element.hpp>

#include <lastfmpp/location.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& location_elem, location& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(location_elem);
    for(auto&& elem : doc) {
        if(elem.name() == "street") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.street({str.data(), str.size()});
        } else if(elem.name() == "city") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.city({str.data(), str.size()});
        } else if(elem.name() == "postalcode") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.post_code({str.data(), str.size()});
        } else if(elem.name() == "country") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.country({str.data(), str.size()});
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_LOCATION

