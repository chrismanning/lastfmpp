/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_TAG_HPP
#define LASTFM_TAG_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/wiki.hpp>
#include <lastfmpp/date.hpp>
#include <lastfmpp/uri.hpp>

namespace lastfmpp {

class service;
struct track;
struct artist;
struct album;
struct wiki;

struct LASTFM_EXPORT tag {
    tag() = default;

    std::experimental::string_view name() const;
    void name(std::experimental::string_view);

    const uri_t& url() const;
    void url(uri_t);

    int reach() const;
    void reach(int);

    int taggings() const;
    void taggings(int);

    bool streamable() const;
    void streamable(bool);

    const wiki& wiki() const;
    void wiki(struct wiki);

    // api methods

    static pplx::task<tag> get_info(service&, std::experimental::string_view name);
    pplx::task<tag> get_info(service&) const;

    static pplx::task<std::vector<tag>> get_similar(service&, std::experimental::string_view name);
    pplx::task<std::vector<tag>> get_similar(service&) const;

    static pplx::task<std::vector<album>>
    get_top_albums(service&, std::experimental::string_view name,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<album>>
    get_top_albums(service&, std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<artist>>
    get_top_artists(service&, std::experimental::string_view name,
                    std::experimental::optional<int> limit = std::experimental::nullopt,
                    std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<artist>>
    get_top_artists(service&, std::experimental::optional<int> limit = std::experimental::nullopt,
                    std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<tag>> get_top_tags(service&);

    static pplx::task<std::vector<track>>
    get_top_tracks(service&, std::experimental::string_view name,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<track>>
    get_top_tracks(service&, std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<artist>> get_weekly_artist_chart(
        service&, std::experimental::string_view name,
        std::experimental::optional<std::tuple<time_point, time_point>> date_range = std::experimental::nullopt,
        std::experimental::optional<int> limit = std::experimental::nullopt);
    pplx::task<std::vector<artist>> get_weekly_artist_chart(
        service&,
        std::experimental::optional<std::tuple<time_point, time_point>> date_range = std::experimental::nullopt,
        std::experimental::optional<int> limit = std::experimental::nullopt) const;

    static pplx::task<std::vector<std::tuple<time_point, time_point>>>
    get_weekly_chart_list(service&, std::experimental::string_view name);
    pplx::task<std::vector<std::tuple<time_point, time_point>>> get_weekly_chart_list(service&) const;

    static pplx::task<std::vector<tag>> search(service&, std::experimental::string_view name,
                                               std::experimental::optional<int> limit = std::experimental::nullopt,
                                               std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<tag>> search(service&, std::experimental::optional<int> limit = std::experimental::nullopt,
                                        std::experimental::optional<int> page = std::experimental::nullopt) const;

  private:
    std::string m_name;
    uri_t m_url;
    int m_reach = 0;
    int m_taggings = 0;
    bool m_streamable = false;
    struct wiki m_wiki;
};

} // namespace lastfm

#endif // LASTFM_TAG_HPP
