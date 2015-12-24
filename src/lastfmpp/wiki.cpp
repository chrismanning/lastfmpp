/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/wiki.hpp>

namespace lastfmpp {

std::experimental::string_view wiki::summary() const {
    return m_summary;
}

void wiki::summary(std::experimental::string_view summary) {
    m_summary = summary.to_string();
}

std::experimental::string_view wiki::content() const {
    return m_content;
}

void wiki::content(std::experimental::string_view content) {
    m_content = content.to_string();
}

time_point wiki::published() const {
    return m_published;
}

void wiki::published(time_point published) {
    m_published = published;
}

} // namespace lastfm
