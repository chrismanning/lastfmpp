/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_AFFILIATION_HPP
#define LASTFM_AFFILIATION_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/uri.hpp>

namespace lastfmpp {

struct LASTFM_EXPORT affiliation {
    affiliation() = default;

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
