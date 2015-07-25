/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_WIKI_HPP
#define LASTFM_WIKI_HPP

#include <string>
#include <experimental/string_view>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/date.hpp>

namespace lastfmpp {

struct LASTFM_EXPORT wiki {
    wiki() = default;

    std::string_view summary() const;
    void summary(std::string_view);

    std::string_view content() const;
    void content(std::string_view);

    date_t published() const;
    void published(date_t);

  private:
    std::string m_summary;
    std::string m_content;
    date_t m_published;
};

} // namespace lastfm

#endif // LASTFM_WIKI_HPP
