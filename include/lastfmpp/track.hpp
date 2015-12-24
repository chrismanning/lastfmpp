/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_TRACK_HPP
#define LASTFM_TRACK_HPP

#include <lastfmpp/album.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/mbid.hpp>

namespace lastfmpp {

class service;
struct tag;

struct LASTFM_EXPORT track {
    track() = default;

    std::experimental::string_view name() const;
    void name(std::experimental::string_view);

    const artist& artist() const;
    void artist(struct artist);

    const album& album() const;
    void album(struct album);

    int tracknumber() const;
    void tracknumber(int);

    std::chrono::milliseconds duration() const;
    void duration(std::chrono::milliseconds);

    const std::vector<tag>& top_tags() const;
    void top_tags(std::vector<tag>);

    const std::vector<track>& similar() const;
    void similar(std::vector<track>);

    const uri_t& url() const;
    void url(uri_t);

    int listeners() const;
    void listeners(int);

    int plays() const;
    void plays(int);

    bool streamable() const;
    void streamable(bool);

    const wiki& wiki() const;
    void wiki(struct wiki);

    mbid_t mbid() const;
    void mbid(mbid_t);

    // api methods

    static pplx::task<track>
    get_info(service&, mbid_t mbid,
             std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt);
    static pplx::task<track>
    get_info(service&, std::experimental::string_view name, std::experimental::string_view artist,
             std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt);
    pplx::task<track>
    get_info(service&, std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt) const;

    static pplx::task<std::vector<affiliation>>
    get_buy_links(service&, mbid_t mbid, std::experimental::string_view countrycode, bool autocorrect = false);
    static pplx::task<std::vector<affiliation>> get_buy_links(service&, std::experimental::string_view name,
                                                              std::experimental::string_view artist,
                                                              std::experimental::string_view countrycode,
                                                              bool autocorrect = false);
    pplx::task<std::vector<affiliation>> get_buy_links(service&, std::experimental::string_view countrycode,
                                                       bool autocorrect = false) const;

    static pplx::task<track> get_correction(service&, std::experimental::string_view name,
                                            std::experimental::string_view artist);
    pplx::task<track> get_correction(service&) const;

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

    static pplx::task<std::vector<track>>
    get_similar(service&, mbid_t mbid, bool autocorrect = false,
                std::experimental::optional<int> limit = std::experimental::nullopt);
    static pplx::task<std::vector<track>>
    get_similar(service&, std::experimental::string_view name, std::experimental::string_view artist,
                bool autocorrect = false, std::experimental::optional<int> limit = std::experimental::nullopt);
    pplx::task<std::vector<track>>
    get_similar(service&, bool autocorrect = false,
                std::experimental::optional<int> limit = std::experimental::nullopt) const;

    static pplx::task<std::vector<user>>
    get_top_fans(service&, mbid_t mbid, bool autocorrect = false,
                 std::experimental::optional<int> limit = std::experimental::nullopt,
                 std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<user>>
    get_top_fans(service&, std::experimental::string_view name, std::experimental::string_view artist,
                 bool autocorrect = false, std::experimental::optional<int> limit = std::experimental::nullopt,
                 std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<user>>
    get_top_fans(service&, bool autocorrect = false,
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

    static pplx::task<std::vector<track>>
    search(service&, std::experimental::string_view name,
           std::experimental::optional<std::experimental::string_view> artist = std::experimental::nullopt,
           std::experimental::optional<int> limit = std::experimental::nullopt,
           std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<track>> search(service&, std::experimental::optional<int> limit = std::experimental::nullopt,
                                          std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<void> update_now_playing(
        service&, std::experimental::string_view title, std::experimental::string_view artist,
        std::experimental::optional<std::experimental::string_view> album = std::experimental::nullopt,
        std::experimental::optional<int> tracknumber = std::experimental::nullopt,
        std::experimental::optional<std::chrono::seconds> duration = std::experimental::nullopt,
        std::experimental::optional<std::experimental::string_view> album_artist = std::experimental::nullopt);
    pplx::task<void> update_now_playing(service&) const;

  private:
    std::string m_name;
    struct artist m_artist;
    struct album m_album;
    int m_tracknumber = 0;
    std::chrono::milliseconds m_duration{0};
    std::vector<tag> m_tags;
    std::vector<track> m_similar;
    uri_t m_url;
    int m_listeners = 0;
    int m_plays = 0;
    bool m_streamable = false;
    struct wiki m_wiki;
    mbid_t m_mbid{{0}};
};

} // namespace lastfm

#endif // LASTFM_TRACK_HPP
