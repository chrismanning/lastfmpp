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
    explicit track() = default;

    std::string_view name() const;
    void name(std::string_view);

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

    static pplx::task<track> get_info(service&, mbid_t mbid, std::optional<std::string_view> lang = std::nullopt,
                                      bool autocorrect = false,
                                      std::optional<std::string_view> username = std::nullopt);
    static pplx::task<track> get_info(service&, std::string_view name, std::string_view artist,
                                      std::optional<std::string_view> lang = std::nullopt, bool autocorrect = false,
                                      std::optional<std::string_view> username = std::nullopt);
    pplx::task<track> get_info(service&, std::optional<std::string_view> lang = std::nullopt, bool autocorrect = false,
                               std::optional<std::string_view> username = std::nullopt) const;

    static pplx::task<std::vector<affiliation>> get_buy_links(service&, mbid_t mbid, std::string_view countrycode,
                                                              bool autocorrect = false);
    static pplx::task<std::vector<affiliation>> get_buy_links(service&, std::string_view name, std::string_view artist,
                                                              std::string_view countrycode, bool autocorrect = false);
    pplx::task<std::vector<affiliation>> get_buy_links(service&, std::string_view countrycode,
                                                       bool autocorrect = false) const;

    static pplx::task<track> get_correction(service&, std::string_view name, std::string_view artist);
    pplx::task<track> get_correction(service&) const;

    static pplx::task<std::vector<shout>> get_shouts(service&, mbid_t mbid, bool autocorrect = false,
                                                     std::optional<int> limit = std::nullopt,
                                                     std::optional<int> page = std::nullopt);
    static pplx::task<std::vector<shout>> get_shouts(service&, std::string_view name, std::string_view artist,
                                                     bool autocorrect = false, std::optional<int> limit = std::nullopt,
                                                     std::optional<int> page = std::nullopt);
    pplx::task<std::vector<shout>> get_shouts(service&, bool autocorrect = false,
                                              std::optional<int> limit = std::nullopt,
                                              std::optional<int> page = std::nullopt) const;

    static pplx::task<std::vector<track>> get_similar(service&, mbid_t mbid, bool autocorrect = false,
                                                      std::optional<int> limit = std::nullopt);
    static pplx::task<std::vector<track>> get_similar(service&, std::string_view name, std::string_view artist,
                                                      bool autocorrect = false,
                                                      std::optional<int> limit = std::nullopt);
    pplx::task<std::vector<track>> get_similar(service&, bool autocorrect = false,
                                               std::optional<int> limit = std::nullopt) const;

    static pplx::task<std::vector<user>> get_top_fans(service&, mbid_t mbid, bool autocorrect = false,
                                                      std::optional<int> limit = std::nullopt,
                                                      std::optional<int> page = std::nullopt);
    static pplx::task<std::vector<user>> get_top_fans(service&, std::string_view name, std::string_view artist,
                                                      bool autocorrect = false, std::optional<int> limit = std::nullopt,
                                                      std::optional<int> page = std::nullopt);
    pplx::task<std::vector<user>> get_top_fans(service&, bool autocorrect = false,
                                               std::optional<int> limit = std::nullopt,
                                               std::optional<int> page = std::nullopt) const;

    static pplx::task<std::vector<tag>> get_top_tags(service&, mbid_t mbid, bool autocorrect = false,
                                                     std::optional<int> limit = std::nullopt,
                                                     std::optional<int> page = std::nullopt);
    static pplx::task<std::vector<tag>> get_top_tags(service&, std::string_view name, std::string_view artist,
                                                     bool autocorrect = false, std::optional<int> limit = std::nullopt,
                                                     std::optional<int> page = std::nullopt);
    pplx::task<std::vector<tag>> get_top_tags(service&, bool autocorrect = false,
                                              std::optional<int> limit = std::nullopt,
                                              std::optional<int> page = std::nullopt) const;

    static pplx::task<std::vector<tag>> get_tags(service&, mbid_t mbid, std::string_view username,
                                                 bool autocorrect = false, std::optional<int> limit = std::nullopt,
                                                 std::optional<int> page = std::nullopt);
    static pplx::task<std::vector<tag>> get_tags(service&, std::string_view name, std::string_view artist,
                                                 std::string_view username, bool autocorrect = false,
                                                 std::optional<int> limit = std::nullopt,
                                                 std::optional<int> page = std::nullopt);
    pplx::task<std::vector<tag>> get_tags(service&, std::string_view username, bool autocorrect = false,
                                          std::optional<int> limit = std::nullopt,
                                          std::optional<int> page = std::nullopt) const;

    static pplx::task<std::vector<track>> search(service&, std::string_view name,
                                                 std::optional<std::string_view> artist = std::nullopt,
                                                 std::optional<int> limit = std::nullopt,
                                                 std::optional<int> page = std::nullopt);
    pplx::task<std::vector<track>> search(service&, std::optional<int> limit = std::nullopt,
                                          std::optional<int> page = std::nullopt) const;

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
