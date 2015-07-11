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
    } catch(...) {}
}

} // namespace boost::uuids

#endif // LASTFM_DESERIALISE_MBID

