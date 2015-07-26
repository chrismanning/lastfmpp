/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_USER
#define LASTFM_DESERIALISE_USER

#include <jbson/element.hpp>

#include <lastfmpp/user.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& user_elem, user& var) {
    //    auto doc = jbson::get<jbson::element_type::document_element>(user_elem);
    //    for(auto&& elem : doc) {
    //    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_USER
