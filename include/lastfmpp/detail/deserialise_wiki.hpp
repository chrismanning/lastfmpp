/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_WIKI
#define LASTFM_DESERIALISE_WIKI

#include <jbson/element.hpp>

#include <lastfmpp/wiki.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& elem, wiki& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(elem);
    for(auto&& elem : doc) {
        if(elem.name() == "summary") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.summary({str.data(), str.size()});
        } else if(elem.name() == "content") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.content({str.data(), str.size()});
        } else if(elem.name() == "published") {
            var.published(jbson::get<time_point>(elem));
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_WIKI
