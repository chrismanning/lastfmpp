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

#ifndef LASTFM_IMAGE_HPP
#define LASTFM_IMAGE_HPP

#include <unordered_map>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/uri.hpp>

namespace lastfmpp {

enum class image_size { small, medium, large, extralarge, mega };

struct LASTFM_EXPORT image {
    explicit image() = default;

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
