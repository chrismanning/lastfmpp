/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/affiliation.hpp>

namespace lastfmpp {

std::experimental::string_view affiliation::supplier_name() const {
    return m_supplier_name;
}

void affiliation::supplier_name(std::experimental::string_view supplier_name) {
    m_supplier_name = supplier_name.to_string();
}

const uri_t& affiliation::buy_link() const {
    return m_buy_link;
}

void affiliation::buy_link(uri_t buy_link) {
    m_buy_link = std::move(buy_link);
}

std::experimental::string_view affiliation::price() const {
    return m_price;
}

void affiliation::price(std::experimental::string_view price) {
    m_price = price.to_string();
}

const uri_t& affiliation::supplier_icon() const {
    return m_supplier_icon;
}

void affiliation::supplier_icon(uri_t supplier_icon) {
    m_supplier_icon = std::move(supplier_icon);
}

bool affiliation::is_search() const {
    return m_is_search;
}

void affiliation::is_search(bool is_search) {
    m_is_search = is_search;
}

} // namespace lastfm
