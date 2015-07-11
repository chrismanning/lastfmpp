/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/image.hpp>

namespace lastfmpp {

const uri_t& image::uri() const {
    return m_uri;
}

void image::uri(uri_t uri) {
    m_uri = std::move(uri);
}

image_size image::size() const {
    return m_size;
}

void image::size(image_size size) {
    m_size = size;
}

} // namespace lastfm
