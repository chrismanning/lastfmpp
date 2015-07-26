/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_ERROR_HPP
#define LASTFM_ERROR_HPP

#include <jbson/document.hpp>

#include <lastfmpp/error.hpp>

namespace lastfmpp::detail {

template <typename ContainerT>
[[noreturn]] inline void handle_error_response(const jbson::basic_element<ContainerT>& elem) {
    auto error = static_cast<api_error>(jbson::get<int>(elem));
    throw api_exception(error);
}

template <typename ContainerT, typename EContainerT>
inline void check_error(const jbson::basic_document<ContainerT, EContainerT>& doc) {
    for(auto&& elem : doc) {
        if(elem.name() == "error") {
            handle_error_response(elem);
        }
    }
}

} // namespace lastfmpp::detail

#endif // LASTFM_ERROR_HPP
