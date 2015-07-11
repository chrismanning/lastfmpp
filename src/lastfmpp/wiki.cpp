/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/wiki.hpp>

namespace lastfmpp {

std::string_view wiki::summary() const {
    return m_summary;
}

void wiki::summary(std::string_view summary) {
    m_summary = summary.to_string();
}

std::string_view wiki::content() const {
    return m_content;
}

void wiki::content(std::string_view content) {
    m_content = content.to_string();
}

date_t wiki::published() const {
    return m_published;
}

void wiki::published(date_t published) {
    m_published = published;
}

} // namespace lastfm
