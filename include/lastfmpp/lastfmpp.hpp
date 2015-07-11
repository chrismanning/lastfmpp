/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
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
