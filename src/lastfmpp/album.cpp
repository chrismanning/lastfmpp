/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <lastfmpp/album.hpp>
#include <lastfmpp/detail/service_access.hpp>
#include <lastfmpp/track.hpp>
#include <lastfmpp/detail/params.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/deserialise_album.hpp>
#include <lastfmpp/detail/deserialise_affiliation.hpp>
#include <lastfmpp/detail/deserialise_shout.hpp>
#include <lastfmpp/detail/deserialise_tag.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>

namespace lastfmpp {

std::experimental::string_view album::name() const {
    return m_name;
}

void album::name(std::experimental::string_view name) {
    m_name = name.to_string();
}

const artist& album::artist() const {
    return m_artist;
}

void album::artist(struct artist artist) {
    m_artist = artist;
}

const uri_t& album::url() const {
    return m_url;
}

void album::url(uri_t url) {
    m_url = std::move(url);
}

day_point album::release_date() const {
    return m_release_date;
}

void album::release_date(day_point release_date) {
    m_release_date = release_date;
}

const std::vector<track>& album::tracks() const {
    return m_tracks;
}

void album::tracks(std::vector<track> tracks) {
    m_tracks = tracks;
}

const std::vector<tag>& album::top_tags() const {
    return m_top_tags;
}

void album::top_tags(std::vector<tag> tags) {
    m_top_tags = std::move(tags);
}

int album::listeners() const {
    return m_listeners;
}

void album::listeners(int listeners) {
    m_listeners = listeners;
}

int album::plays() const {
    return m_plays;
}

void album::plays(int plays) {
    m_plays = plays;
}

bool album::streamable() const {
    return m_streamable;
}

void album::streamable(bool streamable) {
    m_streamable = streamable;
}

const wiki& album::wiki() const {
    return m_wiki;
}

void album::wiki(struct wiki wiki) {
    m_wiki = wiki;
}

const std::vector<shout>& album::shouts() const {
    return m_shouts;
}

void album::shouts(std::vector<shout> shouts) {
    m_shouts = std::move(shouts);
}

const std::vector<image>& album::images() const {
    return m_images;
}

void album::images(std::vector<image> images) {
    m_images = std::move(images);
}

mbid_t album::mbid() const {
    return m_mbid;
}

void album::mbid(mbid_t mbid) {
    m_mbid = mbid;
}

pplx::task<album> album::get_info(service& serv, mbid_t mbid,
                                  std::experimental::optional<std::experimental::string_view> lang, bool autocorrect,
                                  std::experimental::optional<std::experimental::string_view> username) {
    return detail::service_access::get(serv, "album.getinfo",
                                       detail::make_params(std::make_pair("mbid", mbid), std::make_pair("lang", lang),
                                                           std::make_pair("autocorrect", autocorrect),
                                                           std::make_pair("username", username)),
                                       transform_select<album>("album"));
}

pplx::task<album> album::get_info(service& serv, std::experimental::string_view name,
                                  std::experimental::string_view artist,
                                  std::experimental::optional<std::experimental::string_view> lang, bool autocorrect,
                                  std::experimental::optional<std::experimental::string_view> username) {
    return detail::service_access::get(
        serv, "album.getinfo",
        detail::make_params(std::make_pair("album", name), std::make_pair("artist", artist),
                            std::make_pair("lang", lang), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("username", username)),
        transform_select<album>("album"));
}

pplx::task<album> album::get_info(service& serv, std::experimental::optional<std::experimental::string_view> lang,
                                  bool autocorrect,
                                  std::experimental::optional<std::experimental::string_view> username) const {
    if(!m_mbid.is_nil())
        return get_info(serv, m_mbid, lang, autocorrect, username);
    return get_info(serv, m_name, m_artist.name(), lang, autocorrect, username);
}

pplx::task<std::vector<affiliation>> album::get_buy_links(service& serv, mbid_t mbid,
                                                          std::experimental::string_view country, bool autocorrect) {
    return detail::service_access::get(serv, "album.getbuylinks",
                                       detail::make_params(std::make_pair("mbid", mbid),
                                                           std::make_pair("countrycode", country),
                                                           std::make_pair("autocorrect", autocorrect)),
                                       transform_select<std::vector<affiliation>>("affiliations.*.affiliation.*"));
}

pplx::task<std::vector<affiliation>> album::get_buy_links(service& serv, std::experimental::string_view name,
                                                          std::experimental::string_view artist,
                                                          std::experimental::string_view country, bool autocorrect) {
    return detail::service_access::get(
        serv, "album.getbuylinks",
        detail::make_params(std::make_pair("album", name), std::make_pair("artist", artist),
                            std::make_pair("country", country), std::make_pair("autocorrect", autocorrect)),
        transform_select<std::vector<affiliation>>("affiliations.*.affiliation.*"));
}

pplx::task<std::vector<affiliation>> album::get_buy_links(service& serv, std::experimental::string_view country,
                                                          bool autocorrect) const {
    if(!m_mbid.is_nil())
        return get_buy_links(serv, m_mbid, country, autocorrect);
    return get_buy_links(serv, m_name, m_artist.name(), country, autocorrect);
}

pplx::task<std::vector<shout>> album::get_shouts(service& serv, mbid_t mbid, bool autocorrect,
                                                 std::experimental::optional<int> limit,
                                                 std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "album.getshouts",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<shout>>("shouts.shout.*"));
}

pplx::task<std::vector<shout>> album::get_shouts(service& serv, std::experimental::string_view name,
                                                 std::experimental::string_view artist, bool autocorrect,
                                                 std::experimental::optional<int> limit,
                                                 std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "album.getshouts", detail::make_params(std::make_pair("album", name), std::make_pair("artist", artist),
                                                     std::make_pair("autocorrect", autocorrect),
                                                     std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<shout>>("shouts.shout.*"));
}

pplx::task<std::vector<shout>> album::get_shouts(service& serv, bool autocorrect,
                                                 std::experimental::optional<int> limit,
                                                 std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_shouts(serv, m_mbid, autocorrect, limit, page);
    return get_shouts(serv, m_name, m_artist.name(), autocorrect, limit, page);
}

pplx::task<std::vector<tag>> album::get_top_tags(service& serv, mbid_t mbid, bool autocorrect,
                                                 std::experimental::optional<int> limit,
                                                 std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "album.gettoptags",
        detail::make_params(std::make_pair("mbid", mbid), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("toptags.tag.*"));
}

pplx::task<std::vector<tag>> album::get_top_tags(service& serv, std::experimental::string_view name,
                                                 std::experimental::string_view artist, bool autocorrect,
                                                 std::experimental::optional<int> limit,
                                                 std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "album.gettoptags", detail::make_params(std::make_pair("album", name), std::make_pair("artist", artist),
                                                      std::make_pair("autocorrect", autocorrect),
                                                      std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("toptags.tag.*"));
}

pplx::task<std::vector<tag>> album::get_top_tags(service& serv, bool autocorrect,
                                                 std::experimental::optional<int> limit,
                                                 std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_top_tags(serv, m_mbid, autocorrect, limit, page);
    return get_top_tags(serv, m_name, m_artist.name(), autocorrect, limit, page);
}

pplx::task<std::vector<tag>> album::get_tags(service& serv, mbid_t mbid, std::experimental::string_view username,
                                             bool autocorrect, std::experimental::optional<int> limit,
                                             std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "album.gettags", detail::make_params(std::make_pair("mbid", mbid), std::make_pair("user", username),
                                                   std::make_pair("autocorrect", autocorrect),
                                                   std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("tags.tag.*"));
}

pplx::task<std::vector<tag>> album::get_tags(service& serv, std::experimental::string_view name,
                                             std::experimental::string_view artist,
                                             std::experimental::string_view username, bool autocorrect,
                                             std::experimental::optional<int> limit,
                                             std::experimental::optional<int> page) {
    return detail::service_access::get(
        serv, "album.gettags",
        detail::make_params(std::make_pair("album", name), std::make_pair("artist", artist),
                            std::make_pair("user", username), std::make_pair("autocorrect", autocorrect),
                            std::make_pair("limit", limit), std::make_pair("page", page)),
        transform_select<std::vector<tag>>("tags.tag.*"));
}

pplx::task<std::vector<tag>> album::get_tags(service& serv, std::experimental::string_view username, bool autocorrect,
                                             std::experimental::optional<int> limit,
                                             std::experimental::optional<int> page) const {
    if(!m_mbid.is_nil())
        return get_tags(serv, m_mbid, username, autocorrect, limit, page);
    return get_tags(serv, m_name, m_artist.name(), username, autocorrect, limit, page);
}

pplx::task<std::vector<album>> album::search(service& serv, std::experimental::string_view name,
                                             std::experimental::optional<int> limit,
                                             std::experimental::optional<int> page) {
    return detail::service_access::get(serv, "album.search", detail::make_params(std::make_tuple("album", name),
                                                                                 std::make_tuple("limit", limit),
                                                                                 std::make_tuple("page", page)),
                                       transform_select<std::vector<album>>("results.albummatches.album.*"));
}

pplx::task<std::vector<album>> album::search(service& serv, std::experimental::optional<int> limit,
                                             std::experimental::optional<int> page) const {
    return search(serv, m_name, limit, page);
}

} // namespace lastfm
