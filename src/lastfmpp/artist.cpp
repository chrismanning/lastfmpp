/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/detail/service_access.hpp>
#include <lastfmpp/album.hpp>
#include <lastfmpp/track.hpp>
#include <lastfmpp/user.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/detail/params.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_artist.hpp>
#include <lastfmpp/detail/deserialise_event.hpp>
#include <lastfmpp/detail/deserialise_shout.hpp>
#include <lastfmpp/detail/deserialise_album.hpp>
#include <lastfmpp/detail/deserialise_user.hpp>

namespace lastfmpp {

std::experimental::string_view artist::name() const {
    return m_name;
}

void artist::name(std::experimental::string_view name) {
    m_name = name.to_string();
}

const uri_t& artist::url() const {
    return m_url;
}

void artist::url(uri_t url) {
    m_url = std::move(url);
}

const std::vector<artist>& artist::similar() const {
    return m_similar;
}

void artist::similar(std::vector<artist> similar) {
    m_similar = std::move(similar);
}

const std::vector<tag>& artist::top_tags() const {
    return m_tags;
}

void artist::top_tags(std::vector<tag> tags) {
    m_tags = std::move(tags);
}

int artist::listeners() const {
    return m_listeners;
}

void artist::listeners(int listeners) {
    m_listeners = listeners;
}

int artist::plays() const {
    return m_plays;
}

void artist::plays(int plays) {
    m_plays = plays;
}

bool artist::streamable() const {
    return m_streamable;
}

void artist::streamable(bool streamable) {
    m_streamable = streamable;
}

const wiki& artist::wiki() const {
    return m_wiki;
}

void artist::wiki(struct wiki wiki) {
    m_wiki = wiki;
}

const std::vector<image>& artist::images() const {
    return m_images;
}

void artist::images(std::vector<image> images) {
    m_images = std::move(images);
}

mbid_t artist::mbid() const {
    return m_mbid;
}

void artist::mbid(mbid_t mbid) {
    m_mbid = mbid;
}

pplx::task<artist> artist::get_info(service& serv, mbid_t mbid,
                                    std::experimental::optional<std::experimental::string_view> lang, bool autocorrect,
                                    std::experimental::optional<std::experimental::string_view> username) {
    return detail::service_access::get(serv, "artist.getinfo",
                                       detail::make_params(std::make_pair("mbid", mbid), std::make_pair("lang", lang),
                                                           std::make_pair("autocorrect", autocorrect),
                                                           std::make_pair("username", username)),
                                       transform_select<artist>("artist"));
}

pplx::task<artist> artist::get_info(service& serv, std::experimental::string_view name,
                                    std::experimental::optional<std::experimental::string_view> lang, bool autocorrect,
                                    std::experimental::optional<std::experimental::string_view> username) {
    return detail::service_access::get(serv, "artist.getinfo",
                                       detail::make_params(std::make_pair("artist", name), std::make_pair("lang", lang),
                                                           std::make_pair("autocorrect", autocorrect),
                                                           std::make_pair("username", username)),
                                       transform_select<artist>("artist"));
}

pplx::task<artist> artist::get_info(service& serv, std::experimental::optional<std::experimental::string_view> lang,
                                    bool autocorrect,
                                    std::experimental::optional<std::experimental::string_view> username) const {
    return get_info(serv, m_name, lang, autocorrect, username);
}

pplx::task<artist> artist::get_correction(service& serv, std::experimental::string_view name) {
    return detail::service_access::get(serv, "artist.getcorrection",
                                       detail::make_params(std::make_pair("artist", name)),
                                       transform_select<artist>("corrections.correction.artist"));
}

pplx::task<artist> artist::get_correction(service& serv) const {
    return get_correction(serv, m_name);
}

pplx::task<std::vector<event>> artist::get_events(service& serv, mbid_t mbid, bool autocorrect, bool festivalsonly,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.getevents",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("festivalsonly", festivalsonly), std::make_pair("limit", limit),
                            std::make_pair("page", page)),
        transform_select<std::vector<event>>("events.event.*"));
}

pplx::task<std::vector<event>> artist::get_events(service& serv, std::experimental::string_view name, bool autocorrect,
                                                  bool festivalsonly, std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.getevents",
        detail::make_params(std::make_pair("artist", name), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("festivalsonly", festivalsonly), std::make_pair("limit", limit),
                            std::make_pair("page", page)),
        transform_select<std::vector<event>>("events.event.*"));
}

pplx::task<std::vector<event>> artist::get_events(service& serv, bool autocorrect, bool festivalsonly,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_events(serv, m_mbid, autocorrect, festivalsonly, limit, page);
    return get_events(serv, m_name, autocorrect, festivalsonly, limit, page);
}

pplx::task<std::vector<event>> artist::get_past_events(service& serv, mbid_t mbid, bool autocorrect,
                                                       std::experimental::optional<int> limit,
                                                       std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.getpastevents",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<event>>("events.event.*"));
}

pplx::task<std::vector<event>> artist::get_past_events(service& serv, std::experimental::string_view name,
                                                       bool autocorrect, std::experimental::optional<int> limit,
                                                       std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.getpastevents",
        detail::make_params(std::make_pair("artist", name), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<event>>("events.event.*"));
}

pplx::task<std::vector<event>> artist::get_past_events(service& serv, bool autocorrect,
                                                       std::experimental::optional<int> limit,
                                                       std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_past_events(serv, m_mbid, autocorrect, limit, page);
    return get_past_events(serv, m_name, autocorrect, limit, page);
}

pplx::task<std::vector<shout>> artist::get_shouts(service& serv, mbid_t mbid, bool autocorrect,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.getshouts",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<shout>>("shouts.shout.*"));
}

pplx::task<std::vector<shout>> artist::get_shouts(service& serv, std::experimental::string_view name, bool autocorrect,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.getshouts",
        detail::make_params(std::make_pair("artist", name), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<shout>>("shouts.shout.*"));
}

pplx::task<std::vector<shout>> artist::get_shouts(service& serv, bool autocorrect,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_shouts(serv, m_mbid, autocorrect, limit, page);
    return get_shouts(serv, m_name, autocorrect, limit, page);
}

pplx::task<std::vector<artist>> artist::get_similar(service& serv, mbid_t mbid, bool autocorrect,
                                                    std::experimental::optional<int> limit) {
    return detail::service_access::get(serv, "artist.getsimilar",
                                       detail::make_params(std::make_pair("mbid", mbid),
                                                           std::make_pair("autocorrect", autocorrect),
                                                           std::make_pair("limit", limit)),
                                       transform_select<std::vector<artist>>("similarartists.artist.*"));
}

pplx::task<std::vector<artist>> artist::get_similar(service& serv, std::experimental::string_view name,
                                                    bool autocorrect, std::experimental::optional<int> limit) {
    return detail::service_access::get(serv, "artist.getsimilar",
                                       detail::make_params(std::make_pair("artist", name),
                                                           std::make_pair("autocorrect", autocorrect),
                                                           std::make_pair("limit", limit)),
                                       transform_select<std::vector<artist>>("similarartists.artist.*"));
}

pplx::task<std::vector<artist>> artist::get_similar(service& serv, bool autocorrect,
                                                    std::experimental::optional<int> limit) const {
    if(!m_mbid.is_nil())
        return get_similar(serv, m_mbid, autocorrect, limit);
    return get_similar(serv, m_name, autocorrect, limit);
}

pplx::task<std::vector<tag>> artist::get_tags(service& serv, mbid_t mbid, std::experimental::string_view username,
                                              bool autocorrect, std::experimental::optional<int> limit,
                                              std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettags", detail::make_params(std::make_pair("mbid", mbid), std::make_pair("username", username),
                                                    std::make_pair("autocorrect", autocorrect),
                                                    std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("tags.tag.*"));
}

pplx::task<std::vector<tag>> artist::get_tags(service& serv, std::experimental::string_view name,
                                              std::experimental::string_view username, bool autocorrect,
                                              std::experimental::optional<int> limit,
                                              std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettags",
        detail::make_params(std::make_pair("artist", name), std::make_pair("username", username),
                            std::make_pair("autocorrect", autocorrect), std::make_pair("limit", limit),
                            std::make_pair("page", page)),
        transform_select<std::vector<tag>>("tags.tag.*"));
}

pplx::task<std::vector<tag>> artist::get_tags(service& serv, std::experimental::string_view username, bool autocorrect,
                                              std::experimental::optional<int> limit,
                                              std::experimental::optional<int> page) const {
    return get_tags(serv, m_name, username, autocorrect, limit, page);
}

pplx::task<std::vector<album>> artist::get_top_albums(service& serv, mbid_t mbid, bool autocorrect,
                                                      std::experimental::optional<int> limit,
                                                      std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettopalbums",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<album>>("topalbums.album.*"));
}

pplx::task<std::vector<album>> artist::get_top_albums(service& serv, std::experimental::string_view name,
                                                      bool autocorrect, std::experimental::optional<int> limit,
                                                      std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettopalbums",
        detail::make_params(std::make_pair("artist", name), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<album>>("topalbums.album.*"));
}

pplx::task<std::vector<album>> artist::get_top_albums(service& serv, bool autocorrect,
                                                      std::experimental::optional<int> limit,
                                                      std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_top_albums(serv, m_mbid, autocorrect, limit, page);
    return get_top_albums(serv, m_name, autocorrect, limit, page);
}

pplx::task<std::vector<user>> artist::get_top_fans(service& serv, mbid_t mbid, bool autocorrect,
                                                   std::experimental::optional<int> limit,
                                                   std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettopfans",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<user>>("topfans.user.*"));
}

pplx::task<std::vector<user>> artist::get_top_fans(service& serv, std::experimental::string_view name, bool autocorrect,
                                                   std::experimental::optional<int> limit,
                                                   std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettopfans",
        detail::make_params(std::make_pair("artist", name), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<user>>("topfans.user.*"));
}

pplx::task<std::vector<user>> artist::get_top_fans(service& serv, bool autocorrect,
                                                   std::experimental::optional<int> limit,
                                                   std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_top_fans(serv, m_mbid, autocorrect, limit, page);
    return get_top_fans(serv, m_name, autocorrect, limit, page);
}

pplx::task<std::vector<tag>> artist::get_top_tags(service& serv, mbid_t mbid, bool autocorrect,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettoptags",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("toptags.tag.*"));
}

pplx::task<std::vector<tag>> artist::get_top_tags(service& serv, std::experimental::string_view name, bool autocorrect,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettoptags",
        detail::make_params(std::make_pair("artist", name), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("toptags.tag.*"));
}

pplx::task<std::vector<tag>> artist::get_top_tags(service& serv, bool autocorrect,
                                                  std::experimental::optional<int> limit,
                                                  std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_top_tags(serv, m_mbid, autocorrect, limit, page);
    return get_top_tags(serv, m_name, autocorrect, limit, page);
}

pplx::task<std::vector<track>> artist::get_top_tracks(service& serv, mbid_t mbid, bool autocorrect,
                                                      std::experimental::optional<int> limit,
                                                      std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettoptracks",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<track>>("toptracks.track.*"));
}

pplx::task<std::vector<track>> artist::get_top_tracks(service& serv, std::experimental::string_view name,
                                                      bool autocorrect, std::experimental::optional<int> limit,
                                                      std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "artist.gettoptracks",
        detail::make_params(std::make_pair("artist", name), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<track>>("toptracks.track.*"));
}

pplx::task<std::vector<track>> artist::get_top_tracks(service& serv, bool autocorrect,
                                                      std::experimental::optional<int> limit,
                                                      std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_top_tracks(serv, m_mbid, autocorrect, limit, page);
    return get_top_tracks(serv, m_name, autocorrect, limit, page);
}

pplx::task<std::vector<artist>> artist::search(service& serv, std::experimental::string_view name,
                                               std::experimental::optional<int> limit,
                                               std::experimental::optional<int> page) {
    return detail::service_access::get(serv, "artist.search", detail::make_params(std::make_pair("artist", name),
                                                                                  std::make_pair("limit", limit),
                                                                                  std::make_pair("page", page)),
                                       transform_select<std::vector<artist>>("results.artistmatches.artist.*"));
}

pplx::task<std::vector<artist>> artist::search(service& serv, std::experimental::optional<int> limit,
                                               std::experimental::optional<int> page) const {
    return search(serv, m_name, limit, page);
}

} // namespace lastfm
