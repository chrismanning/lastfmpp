/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_EXT
#define LASTFM_DESERIALISE_EXT

#include <chrono>
#include <exception>

#include <jbson/element.hpp>

#include <lastfmpp/uri.hpp>
#include <lastfmpp/date.hpp>

namespace lastfmpp::detail {

    template <typename TimePoint> struct _parse_time_point {
        auto operator()(std::string str) const {
            static constexpr auto fmts = {"%a, %d %b %Y %H:%M:%S", "%d %b %Y, %H:%M", "%d %b %Y"};
            std::tm tm{0};
            std::istringstream ss{str};
            auto fmt = std::begin(fmts);

            do {
                tm = {0};
                ss.clear();
                ss.seekg(0);
                ss >> std::get_time(&tm, *fmt);
            } while(ss.fail() && ++fmt != std::end(fmts));

            if(ss.fail()) {
                BOOST_THROW_EXCEPTION(std::runtime_error("date/time parse failed"));
            }
            return date::floor<typename TimePoint::duration>(TimePoint::clock::from_time_t(std::mktime(&tm)));
        }
    };

    template <typename TimePoint> auto constexpr parse_time_point = _parse_time_point<TimePoint>{};
}

namespace std {
namespace chrono {

template <typename Container, typename Clock, typename Duration>
void value_get(const jbson::basic_element<Container>& elem, time_point<Clock, Duration>& var) {
    var = lastfmpp::detail::parse_time_point<time_point<Clock, Duration>>(jbson::get<std::string>(elem));
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
