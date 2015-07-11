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

#ifndef LASTFM_DESERIALISE_EXT
#define LASTFM_DESERIALISE_EXT

#include <chrono>

#include <jbson/element.hpp>

#include <lastfmpp/uri.hpp>
#include <lastfmpp/date.hpp>

namespace std {
namespace chrono {

template <typename Container> void value_get(const jbson::basic_element<Container>& elem, lastfmpp::date_t& var) {
    std::tm tm;
    auto str = jbson::get<std::string>(elem);
    std::stringstream ss{str};
    ss >> std::get_time(&tm, "%a, %d %b %Y %H:%M:%S");
    var = lastfmpp::date_t::clock::from_time_t(std::mktime(&tm));
}

} // namespace chrono

template <typename Container, typename Elem>
void value_get(const jbson::basic_element<Container>& vector_elem, vector<Elem>& var) {
    auto arr = jbson::get<jbson::element_type::array_element>(vector_elem);
    for(auto&& elem : arr) {
        var.push_back(jbson::get<Elem>(elem));
    }
}

} // namespace std

namespace web {

template <typename Container> void value_get(const jbson::basic_element<Container>& elem, uri& var) {
    auto str = utility::conversions::to_string_t(jbson::get<std::string>(elem));
    var = uri{std::move(str)};
}

} // namespace web


#endif // LASTFM_DESERIALISE_EXT

