/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_SHOUT
#define LASTFM_DESERIALISE_SHOUT

#include <jbson/element.hpp>

#include <lastfmpp/shout.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& elem, shout& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(elem);
    for(auto&& elem : doc) {
        if(elem.name() == "author") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.body({str.data(), str.size()});
        } else if(elem.name() == "body") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.body({str.data(), str.size()});
        } else if(elem.name() == "date") {
            var.date(jbson::get<date_t>(elem));
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_SHOUT
