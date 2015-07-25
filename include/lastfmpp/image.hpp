/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_IMAGE_HPP
#define LASTFM_IMAGE_HPP

#include <unordered_map>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/uri.hpp>

namespace lastfmpp {

enum class image_size { small, medium, large, extralarge, mega };

struct LASTFM_EXPORT image {
    image() = default;

    const uri_t& uri() const;
    void uri(uri_t);

    image_size size() const;
    void size(image_size);

  private:
    uri_t m_uri;
    image_size m_size = image_size::small;
};

} // namespace lastfm

#endif // LASTFM_IMAGE_HPP
