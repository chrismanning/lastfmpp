/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/detail/service_access.hpp>
#include <lastfmpp/tag.hpp>
#include <lastfmpp/user.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/track.hpp>
#include <lastfmpp/detail/params.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/deserialise_track.hpp>
#include <lastfmpp/detail/deserialise_affiliation.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_user.hpp>
#include <lastfmpp/detail/deserialise_tag.hpp>
#include <lastfmpp/detail/deserialise_shout.hpp>

namespace lastfmpp {

std::string_view track::name() const {
    return m_name;
}

void track::name(std::string_view name) {
    m_name = name.to_string();
}

const artist& track::artist() const {
    return m_artist;
}

void track::artist(struct artist artist) {
    m_artist = std::move(artist);
}

const album& track::album() const {
    return m_album;
}

void track::album(struct album album) {
    m_album = std::move(album);
}

int track::tracknumber() const {
    return m_tracknumber;
}

void track::tracknumber(int tracknumber) {
    m_tracknumber = tracknumber;
}

std::chrono::milliseconds track::duration() const {
    return m_duration;
}

void track::duration(std::chrono::milliseconds duration) {
    m_duration = duration;
}

const std::vector<tag>& track::top_tags() const {
    return m_tags;
}

void track::top_tags(std::vector<tag> tags) {
    m_tags = std::move(tags);
}

const std::vector<track>& track::similar() const {
    return m_similar;
}

void track::similar(std::vector<track> similar) {
    m_similar = std::move(similar);
}

const uri_t& track::url() const {
    return m_url;
}

void track::url(uri_t url) {
    m_url = std::move(url);
}

int track::listeners() const {
    return m_listeners;
}

void track::listeners(int listeners) {
    m_listeners = listeners;
}

int track::plays() const {
    return m_plays;
}

void track::plays(int plays) {
    m_plays = plays;
}

bool track::streamable() const {
    return m_streamable;
}

void track::streamable(bool streamable) {
    m_streamable = streamable;
}

const wiki& track::wiki() const {
    return m_wiki;
}

void track::wiki(struct wiki wiki) {
    m_wiki = std::move(wiki);
}

mbid_t track::mbid() const {
    return m_mbid;
}

void track::mbid(mbid_t mbid) {
    m_mbid = mbid;
}

pplx::task<track> track::get_info(service& serv, mbid_t mbid, std::optional<std::string_view> lang, bool autocorrect,
                                  std::optional<std::string_view> username) {
    return detail::service_access::get(serv, "track.getinfo",
                                       detail::make_params(std::make_pair("mbid", mbid), std::make_pair("lang", lang),
                                                           std::make_pair("autocorrect", autocorrect),
                                                           std::make_pair("username", username)),
                                       transform_select<track>("track"));
}

pplx::task<track> track::get_info(service& serv, std::string_view name, std::string_view artist,
                                  std::optional<std::string_view> lang, bool autocorrect,
                                  std::optional<std::string_view> username) {
    return detail::service_access::get(
        serv, "track.getinfo",
        detail::make_params(std::make_pair("track", name), std::make_pair("artist", artist),
                            std::make_pair("lang", lang), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("username", username)),
        transform_select<track>("track"));
}

pplx::task<track> track::get_info(service& serv, std::optional<std::string_view> lang, bool autocorrect,
                                  std::optional<std::string_view> username) const {
    if(!m_mbid.is_nil())
        return get_info(serv, m_mbid, lang, autocorrect, username);
    return get_info(serv, m_name, m_artist.name(), lang, autocorrect, username);
}

pplx::task<std::vector<affiliation>> track::get_buy_links(service& serv, mbid_t mbid, std::string_view countrycode,
                                                          bool autocorrect) {
    return detail::service_access::get(serv, "track.getbuylinks",
                                       detail::make_params(std::make_pair("mbid", mbid),
                                                           std::make_pair("country", countrycode),
                                                           std::make_pair("autocorrect", autocorrect)),
                                       transform_select<std::vector<affiliation>>("affiliations.*.affiliation.*"));
}

pplx::task<std::vector<affiliation>> track::get_buy_links(service& serv, std::string_view name, std::string_view artist,
                                                          std::string_view countrycode, bool autocorrect) {
    return detail::service_access::get(
        serv, "track.getbuylinks",
        detail::make_params(std::make_pair("album", name), std::make_pair("artist", artist),
                            std::make_pair("country", countrycode), std::make_pair("autocorrect", autocorrect)),
        transform_select<std::vector<affiliation>>("affiliations.*.affiliation.*"));
}

pplx::task<std::vector<affiliation>> track::get_buy_links(service& serv, std::string_view countrycode,
                                                          bool autocorrect) const {
    if(!m_mbid.is_nil())
        return get_buy_links(serv, m_mbid, countrycode, autocorrect);
    return get_buy_links(serv, m_name, m_artist.name(), countrycode, autocorrect);
}

pplx::task<track> track::get_correction(service& serv, std::string_view name, std::string_view artist) {
    return detail::service_access::get(
        serv, "track.getcorrection",
        detail::make_params(std::make_pair("track", name), std::make_pair("artist", artist)),
        transform_select<track>("corrections.correction.track"));
}

pplx::task<track> track::get_correction(service& serv) const {
    return get_correction(serv, m_name, m_artist.name());
}

pplx::task<std::vector<shout>> track::get_shouts(service& serv, mbid_t mbid, bool autocorrect, std::optional<int> limit,
                                                 std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.getshouts",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<shout>>("shouts.shout.*"));
}

pplx::task<std::vector<shout>> track::get_shouts(service& serv, std::string_view name, std::string_view artist,
                                                 bool autocorrect, std::optional<int> limit, std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.getshouts", detail::make_params(std::make_pair("track", name), std::make_pair("artist", artist),
                                                     std::make_pair("autocorrect", autocorrect),
                                                     std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<shout>>("shouts.shout.*"));
}

pplx::task<std::vector<shout>> track::get_shouts(service& serv, bool autocorrect, std::optional<int> limit,
                                                 std::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_shouts(serv, m_mbid, autocorrect, limit, page);
    return get_shouts(serv, m_name, m_artist.name(), autocorrect, limit, page);
}

pplx::task<std::vector<track>> track::get_similar(service& serv, mbid_t mbid, bool autocorrect,
                                                  std::optional<int> limit) {
    return detail::service_access::get(serv, "track.getsimilar",
                                       detail::make_params(std::make_pair("mbid", mbid),
                                                           std::make_pair("autocorrect", autocorrect),
                                                           std::make_pair("limit", limit)),
                                       transform_select<std::vector<track>>("similartracks.track.*"));
}

pplx::task<std::vector<track>> track::get_similar(service& serv, std::string_view name, std::string_view artist,
                                                  bool autocorrect, std::optional<int> limit) {
    return detail::service_access::get(
        serv, "track.getsimilar",
        detail::make_params(std::make_pair("track", name), std::make_pair("artist", artist),
                            std::make_pair("autocorrect", autocorrect), std::make_pair("limit", limit)),
        transform_select<std::vector<track>>("similartracks.track.*"));
}

pplx::task<std::vector<track>> track::get_similar(service& serv, bool autocorrect, std::optional<int> limit) const {
    if(!m_mbid.is_nil())
        return get_similar(serv, m_mbid, autocorrect, limit);
    return get_similar(serv, m_name, m_artist.name(), autocorrect, limit);
}

pplx::task<std::vector<user>> track::get_top_fans(service& serv, mbid_t mbid, bool autocorrect,
                                                  std::optional<int> limit, std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.gettopfans",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<user>>("topfans.user.*"));
}

pplx::task<std::vector<user>> track::get_top_fans(service& serv, std::string_view name, std::string_view artist,
                                                  bool autocorrect, std::optional<int> limit, std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.gettopfans", detail::make_params(std::make_pair("track", name), std::make_pair("artist", artist),
                                                      std::make_pair("autocorrect", autocorrect),
                                                      std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<user>>("topfans.user.*"));
}

pplx::task<std::vector<user>> track::get_top_fans(service& serv, bool autocorrect, std::optional<int> limit,
                                                  std::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_top_fans(serv, m_mbid, autocorrect, limit, page);
    return get_top_fans(serv, m_name, m_artist.name(), autocorrect, limit, page);
}

pplx::task<std::vector<tag>> track::get_top_tags(service& serv, mbid_t mbid, bool autocorrect, std::optional<int> limit,
                                                 std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.gettoptags",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("toptags.tag.*"));
}

pplx::task<std::vector<tag>> track::get_top_tags(service& serv, std::string_view name, std::string_view artist,
                                                 bool autocorrect, std::optional<int> limit, std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.gettoptags", detail::make_params(std::make_pair("track", name), std::make_pair("artist", artist),
                                                      std::make_pair("autocorrect", autocorrect),
                                                      std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("toptags.tag.*"));
}

pplx::task<std::vector<tag>> track::get_top_tags(service& serv, bool autocorrect, std::optional<int> limit,
                                                 std::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_top_tags(serv, m_mbid, autocorrect, limit, page);
    return get_top_tags(serv, m_name, m_artist.name(), autocorrect, limit, page);
}

pplx::task<std::vector<tag>> track::get_tags(service& serv, mbid_t mbid, std::string_view username, bool autocorrect,
                                             std::optional<int> limit, std::optional<int> page) {
    return detail::service_access::get(
        serv, "album.gettags", detail::make_params(std::make_pair("mbid", mbid), std::make_pair("user", username),
                                                   std::make_pair("autocorrect", autocorrect),
                                                   std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("tags.tag.*"));
}

pplx::task<std::vector<tag>> track::get_tags(service& serv, std::string_view name, std::string_view artist,
                                             std::string_view username, bool autocorrect, std::optional<int> limit,
                                             std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.gettags",
        detail::make_params(std::make_pair("track", name), std::make_pair("artist", artist),
                            std::make_pair("user", username), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("tags.tag.*"));
}

pplx::task<std::vector<tag>> track::get_tags(service& serv, std::string_view username, bool autocorrect,
                                             std::optional<int> limit, std::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_tags(serv, m_mbid, username, autocorrect, limit, page);
    return get_tags(serv, m_name, m_artist.name(), username, autocorrect, limit, page);
}

pplx::task<std::vector<track>> track::search(service& serv, std::string_view name,
                                             std::optional<std::string_view> artist, std::optional<int> limit,
                                             std::optional<int> page) {
    return detail::service_access::get(
        serv, "track.search", detail::make_params(std::make_tuple("track", name), std::make_tuple("artist", artist),
                                                  std::make_tuple("limit", limit), std::make_tuple("page", page)),
        transform_select<std::vector<track>>("results.trackmatches.track.*"));
}

pplx::task<std::vector<track>> track::search(service& serv, std::optional<int> limit, std::optional<int> page) const {
    return search(serv, m_name, m_artist.name(), limit, page);
}

} // namespace lastfm
