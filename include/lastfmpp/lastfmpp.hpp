/**************************************************************************
**  Copyright (C) 2012 Christian Manning
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

#ifndef LASTFM_HPP
#define LASTFM_HPP

#include <experimental/string_view>
#include <experimental/optional>

#include <pplx/pplxtasks.h>

#include <lastfmpp/exports.hpp>

namespace std {
namespace experimental {}
using namespace experimental;
}

namespace lastfmpp {

constexpr std::string_view operator""_sv(const char* str, size_t len) {
    return {str, len};
}

constexpr std::wstring_view operator""_sv(const wchar_t* str, size_t len) {
    return {str, len};
}

constexpr std::u16string_view operator""_sv(const char16_t* str, size_t len) {
    return {str, len};
}

constexpr std::u32string_view operator""_sv(const char32_t* str, size_t len) {
    return {str, len};
}

} // namespace lastfm

#endif // LASTFM_HPP
