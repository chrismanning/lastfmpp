/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_ALBUM_HPP
#define LASTFM_ALBUM_HPP

#include <string>
#include <vector>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/shout.hpp>
#include <lastfmpp/affiliation.hpp>
#include <lastfmpp/image.hpp>
#include <lastfmpp/tag.hpp>
#include <lastfmpp/mbid.hpp>
#include <lastfmpp/uri.hpp>

namespace lastfmpp {

struct track;

struct LASTFM_EXPORT album {
    album() = default;

    std::experimental::string_view name() const;
    void name(std::experimental::string_view);

    const artist& artist() const;
    void artist(struct artist);

    const uri_t& url() const;
    void url(uri_t);

    day_point release_date() const;
    void release_date(day_point);

    const std::vector<track>& tracks() const;
    void tracks(std::vector<track>);

    const std::vector<tag>& top_tags() const;
    void top_tags(std::vector<tag>);

    int listeners() const;
    void listeners(int);

    int plays() const;
    void plays(int);

    bool streamable() const;
    void streamable(bool);

    const wiki& wiki() const;
    void wiki(struct wiki);

    const std::vector<shout>& shouts() const;
    void shouts(std::vector<shout>);

    const std::vector<image>& images() const;
    void images(std::vector<image>);

    mbid_t mbid() const;
    void mbid(mbid_t);

    // api methods

    static pplx::task<album>
    get_info(service&, mbid_t mbid,
             std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt);
    static pplx::task<album>
    get_info(service&, std::experimental::string_view name, std::experimental::string_view artist,
             std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt);
    pplx::task<album>
    get_info(service&, std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt) const;

    static pplx::task<std::vector<affiliation>>
    get_buy_links(service&, mbid_t mbid, std::experimental::string_view country, bool autocorrect = false);
    static pplx::task<std::vector<affiliation>> get_buy_links(service&, std::experimental::string_view name,
                                                              std::experimental::string_view artist,
                                                              std::experimental::string_view country,
                                                              bool autocorrect = false);
    pplx::task<std::vector<affiliation>> get_buy_links(service&, std::experimental::string_view country,
                                                       bool autocorrect = false) const;

    static pplx::task<std::vector<shout>>
    get_shouts(service&, mbid_t mbid, bool autocorrect = false,
               std::experimental::optional<int> limit = std::experimental::nullopt,
               std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<shout>>
    get_shouts(service&, std::experimental::string_view name, std::experimental::string_view artist,
               bool autocorrect = false, std::experimental::optional<int> limit = std::experimental::nullopt,
               std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<shout>> get_shouts(service&, bool autocorrect = false,
                                              std::experimental::optional<int> limit = std::experimental::nullopt,
                                              std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<tag>>
    get_top_tags(service&, mbid_t mbid, bool autocorrect = false,
                 std::experimental::optional<int> limit = std::experimental::nullopt,
                 std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<tag>>
    get_top_tags(service&, std::experimental::string_view name, std::experimental::string_view artist,
                 bool autocorrect = false, std::experimental::optional<int> limit = std::experimental::nullopt,
                 std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<tag>> get_top_tags(service&, bool autocorrect = false,
                                              std::experimental::optional<int> limit = std::experimental::nullopt,
                                              std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<tag>> get_tags(service&, mbid_t mbid, std::experimental::string_view username,
                                                 bool autocorrect = false,
                                                 std::experimental::optional<int> limit = std::experimental::nullopt,
                                                 std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<tag>> get_tags(service&, std::experimental::string_view name,
                                                 std::experimental::string_view artist,
                                                 std::experimental::string_view username, bool autocorrect = false,
                                                 std::experimental::optional<int> limit = std::experimental::nullopt,
                                                 std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<tag>> get_tags(service&, std::experimental::string_view username, bool autocorrect = false,
                                          std::experimental::optional<int> limit = std::experimental::nullopt,
                                          std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<album>> search(service&, std::experimental::string_view name,
                                                 std::experimental::optional<int> limit = std::experimental::nullopt,
                                                 std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<album>> search(service&, std::experimental::optional<int> limit = std::experimental::nullopt,
                                          std::experimental::optional<int> page = std::experimental::nullopt) const;

  private:
    std::string m_name;
    struct artist m_artist;
    uri_t m_url;
    day_point m_release_date;
    std::vector<tag> m_top_tags;
    std::vector<track> m_tracks;
    int m_listeners = 0;
    int m_plays = 0;
    bool m_streamable = false;
    struct wiki m_wiki;
    std::vector<shout> m_shouts;
    std::vector<image> m_images;
    mbid_t m_mbid{{0}};
};

} // namespace lastfm

#endif // LASTFM_ALBUM_HPP
