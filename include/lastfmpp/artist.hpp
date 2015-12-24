/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_ARTIST_HPP
#define LASTFM_ARTIST_HPP

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/wiki.hpp>
#include <lastfmpp/image.hpp>
#include <lastfmpp/shout.hpp>
#include <lastfmpp/event.hpp>
#include <lastfmpp/tag.hpp>
#include <lastfmpp/mbid.hpp>

namespace lastfmpp {

class service;
struct album;
struct user;
struct track;

struct LASTFM_EXPORT artist {
    artist() = default;

    std::experimental::string_view name() const;
    void name(std::experimental::string_view);

    const uri_t& url() const;
    void url(uri_t);

    const std::vector<artist>& similar() const;
    void similar(std::vector<artist>);

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

    const std::vector<image>& images() const;
    void images(std::vector<image>);

    mbid_t mbid() const;
    void mbid(mbid_t);

    // api methods

    static pplx::task<artist>
    get_info(service&, mbid_t mbid,
             std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt);
    static pplx::task<artist>
    get_info(service&, std::experimental::string_view name,
             std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt);
    pplx::task<artist>
    get_info(service&, std::experimental::optional<std::experimental::string_view> lang = std::experimental::nullopt,
             bool autocorrect = false,
             std::experimental::optional<std::experimental::string_view> username = std::experimental::nullopt) const;

    static pplx::task<artist> get_correction(service&, std::experimental::string_view name);
    pplx::task<artist> get_correction(service&) const;

    static pplx::task<std::vector<event>>
    get_events(service&, mbid_t mbid, bool autocorrect = false, bool festivalsonly = false,
               std::experimental::optional<int> limit = std::experimental::nullopt,
               std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<event>>
    get_events(service&, std::experimental::string_view name, bool autocorrect = false, bool festivalsonly = false,
               std::experimental::optional<int> limit = std::experimental::nullopt,
               std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<event>> get_events(service&, bool autocorrect = false, bool festivalsonly = false,
                                              std::experimental::optional<int> limit = std::experimental::nullopt,
                                              std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<event>>
    get_past_events(service&, mbid_t mbid, bool autocorrect = false,
                    std::experimental::optional<int> limit = std::experimental::nullopt,
                    std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<event>>
    get_past_events(service&, std::experimental::string_view name, bool autocorrect = false,
                    std::experimental::optional<int> limit = std::experimental::nullopt,
                    std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<event>>
    get_past_events(service&, bool autocorrect = false,
                    std::experimental::optional<int> limit = std::experimental::nullopt,
                    std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<shout>>
    get_shouts(service&, mbid_t mbid, bool autocorrect = false,
               std::experimental::optional<int> limit = std::experimental::nullopt,
               std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<shout>>
    get_shouts(service&, std::experimental::string_view name, bool autocorrect = false,
               std::experimental::optional<int> limit = std::experimental::nullopt,
               std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<shout>> get_shouts(service&, bool autocorrect = false,
                                              std::experimental::optional<int> limit = std::experimental::nullopt,
                                              std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<artist>>
    get_similar(service&, mbid_t mbid, bool autocorrect = false,
                std::experimental::optional<int> limit = std::experimental::nullopt);
    static pplx::task<std::vector<artist>>
    get_similar(service&, std::experimental::string_view name, bool autocorrect = false,
                std::experimental::optional<int> limit = std::experimental::nullopt);
    pplx::task<std::vector<artist>>
    get_similar(service&, bool autocorrect = false,
                std::experimental::optional<int> limit = std::experimental::nullopt) const;

    static pplx::task<std::vector<tag>> get_tags(service&, mbid_t mbid, std::experimental::string_view username,
                                                 bool autocorrect = false,
                                                 std::experimental::optional<int> limit = std::experimental::nullopt,
                                                 std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<tag>> get_tags(service&, std::experimental::string_view name,
                                                 std::experimental::string_view username, bool autocorrect = false,
                                                 std::experimental::optional<int> limit = std::experimental::nullopt,
                                                 std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<tag>> get_tags(service&, std::experimental::string_view username, bool autocorrect = false,
                                          std::experimental::optional<int> limit = std::experimental::nullopt,
                                          std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<album>>
    get_top_albums(service&, mbid_t mbid, bool autocorrect = false,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<album>>
    get_top_albums(service&, std::experimental::string_view name, bool autocorrect = false,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<album>>
    get_top_albums(service&, bool autocorrect = false,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<user>>
    get_top_fans(service&, mbid_t mbid, bool autocorrect = false,
                 std::experimental::optional<int> limit = std::experimental::nullopt,
                 std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<user>>
    get_top_fans(service&, std::experimental::string_view name, bool autocorrect = false,
                 std::experimental::optional<int> limit = std::experimental::nullopt,
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
    get_top_tags(service&, std::experimental::string_view name, bool autocorrect = false,
                 std::experimental::optional<int> limit = std::experimental::nullopt,
                 std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<tag>> get_top_tags(service&, bool autocorrect = false,
                                              std::experimental::optional<int> limit = std::experimental::nullopt,
                                              std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<track>>
    get_top_tracks(service&, mbid_t mbid, bool autocorrect = false,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt);
    static pplx::task<std::vector<track>>
    get_top_tracks(service&, std::experimental::string_view name, bool autocorrect = false,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<track>>
    get_top_tracks(service&, bool autocorrect = false,
                   std::experimental::optional<int> limit = std::experimental::nullopt,
                   std::experimental::optional<int> page = std::experimental::nullopt) const;

    static pplx::task<std::vector<artist>> search(service&, std::experimental::string_view name,
                                                  std::experimental::optional<int> limit = std::experimental::nullopt,
                                                  std::experimental::optional<int> page = std::experimental::nullopt);
    pplx::task<std::vector<artist>> search(service&,
                                           std::experimental::optional<int> limit = std::experimental::nullopt,
                                           std::experimental::optional<int> page = std::experimental::nullopt) const;

  private:
    std::string m_name;
    uri_t m_url;
    std::vector<artist> m_similar;
    std::vector<tag> m_tags;
    int m_listeners = 0;
    int m_plays = 0;
    bool m_streamable = false;
    struct wiki m_wiki;
    std::vector<image> m_images;
    mbid_t m_mbid{{0}};
};

} // namespace lastfm

#endif // LASTFM_ARTIST_HPP
