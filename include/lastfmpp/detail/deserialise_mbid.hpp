/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_MBID
#define LASTFM_DESERIALISE_MBID

#include <boost/uuid/string_generator.hpp>

#include <jbson/element.hpp>

#include <lastfmpp/mbid.hpp>

namespace boost::uuids {

template <typename Container> void value_get(const jbson::basic_element<Container>& mbid_elem, uuid& var) {
    static constexpr string_generator gen{};
    auto str = jbson::get<jbson::element_type::string_element>(mbid_elem);
    try {
        var = gen(str.begin(), str.end());
    } catch(...) {
    }
}

} // namespace boost::uuids

#endif // LASTFM_DESERIALISE_MBID
