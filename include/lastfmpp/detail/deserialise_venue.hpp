/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
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
