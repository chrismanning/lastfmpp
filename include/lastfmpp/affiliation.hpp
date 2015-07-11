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

#ifndef LASTFM_AFFILIATION_HPP
#define LASTFM_AFFILIATION_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/uri.hpp>

namespace lastfmpp {

struct LASTFM_EXPORT affiliation {
    explicit affiliation() = default;

    std::string_view supplier_name() const;
    void supplier_name(std::string_view);

    const uri_t& buy_link() const;
    void buy_link(uri_t);

    std::string_view price() const;
    void price(std::string_view);

    const uri_t& supplier_icon() const;
    void supplier_icon(uri_t);

    bool is_search() const;
    void is_search(bool);

  private:
    std::string m_supplier_name;
    uri_t m_buy_link;
    std::string m_price;
    uri_t m_supplier_icon;
    bool m_is_search = false;
};

} // namespace lastfm

#endif // LASTFM_AFFILIATION_HPP
