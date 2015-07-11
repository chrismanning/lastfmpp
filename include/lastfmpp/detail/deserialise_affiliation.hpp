/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_AFFILIATION
#define LASTFM_DESERIALISE_AFFILIATION

#include <jbson/element.hpp>

#include <lastfmpp/affiliation.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& elem, affiliation& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(elem);
    for(auto&& elem : doc) {
        if(elem.name() == "supplierName") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.supplier_name({str.data(), str.size()});
        } else if(elem.name() == "buyLink") {
            var.buy_link(jbson::get<uri_t>(elem));
        } else if(elem.name() == "price") {
            for(auto&& e : jbson::get<jbson::element_type::document_element>(elem)) {
                if(e.name() == "formatted") {
                    auto str = jbson::get<jbson::element_type::string_element>(elem);
                    var.price({str.data(), str.size()});
                }
            }
        } else if(elem.name() == "supplierIcon") {
            var.supplier_icon(jbson::get<uri_t>(elem));
        } else if(elem.name() == "isSearch") {
            var.is_search(jbson::get<jbson::element_type::string_element>(elem) == "1");
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_AFFILIATION

