/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_WIKI_HPP
#define LASTFM_WIKI_HPP

#include <string>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/date.hpp>

namespace lastfmpp {

struct LASTFM_EXPORT wiki {
    wiki() = default;

    std::experimental::string_view summary() const;
    void summary(std::experimental::string_view);

    std::experimental::string_view content() const;
    void content(std::experimental::string_view);

    time_point published() const;
    void published(time_point);

  private:
    std::string m_summary;
    std::string m_content;
    time_point m_published;
};

} // namespace lastfm

#endif // LASTFM_WIKI_HPP
