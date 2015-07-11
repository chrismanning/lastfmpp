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

