/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <jbson/path.hpp>

#include <lastfmpp/tag.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/album.hpp>
#include <lastfmpp/track.hpp>
#include <lastfmpp/service.hpp>
#include <lastfmpp/detail/deserialise_tag.hpp>
#include <lastfmpp/detail/deserialise_album.hpp>
#include <lastfmpp/detail/deserialise_artist.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_track.hpp>

namespace lastfmpp {

std::string_view tag::name() const {
    return m_name;
}

void tag::name(std::string_view name) {
    m_name = name.to_string();
}

const uri_t& tag::url() const {
    return m_url;
}

void tag::url(uri_t url) {
    m_url = std::move(url);
}

int tag::reach() const {
    return m_reach;
}

void tag::reach(int reach) {
    m_reach = reach;
}

int tag::taggings() const {
    return m_taggings;
}

void tag::taggings(int taggings) {
    m_taggings = taggings;
}

bool tag::streamable() const {
    return m_streamable;
}

void tag::streamable(bool streamable) {
    m_streamable = streamable;
}

const wiki& tag::wiki() const {
    return m_wiki;
}

void tag::wiki(struct wiki wiki) {
    m_wiki = wiki;
}

pplx::task<tag> tag::get_info(service& serv, std::string_view name) {
    return serv.get("tag.getinfo", detail::make_params(std::make_pair("tag", name)), transform_select<tag>("tag"));
}

pplx::task<tag> tag::get_info(service& serv) const {
    return get_info(serv, m_name);
}

pplx::task<std::vector<tag>> tag::get_similar(service& serv, std::string_view name) {
    return serv.get("tag.getsimilar", detail::make_params(std::make_pair("tag", name)),
                    transform_select<std::vector<tag>>("similartags.tag.*"));
}

pplx::task<std::vector<tag>> tag::get_similar(service& serv) const {
    return get_similar(serv, m_name);
}

pplx::task<std::vector<album>> tag::get_top_albums(service& serv, std::string_view name, std::optional<int> limit,
                                                   std::optional<int> page) {
    return serv.get("tag.gettopalbums",
                    detail::make_params(std::make_tuple("tag", name), std::make_tuple("limit", limit),
                                        std::make_tuple("page", page)),
                    transform_select<std::vector<album>>("topalbums.album.*"));
}

pplx::task<std::vector<album>> tag::get_top_albums(service& serv, std::optional<int> limit,
                                                   std::optional<int> page) const {
    return get_top_albums(serv, m_name, limit, page);
}

pplx::task<std::vector<artist>> tag::get_top_artists(service& serv, std::string_view name, std::optional<int> limit,
                                                     std::optional<int> page) {
    return serv.get("tag.gettopartists",
                    detail::make_params(std::make_tuple("tag", name), std::make_tuple("limit", limit),
                                        std::make_tuple("page", page)),
                    transform_select<std::vector<artist>>("topartists.artist.*"));
}

pplx::task<std::vector<artist>> tag::get_top_artists(service& serv, std::optional<int> limit,
                                                     std::optional<int> page) const {
    return get_top_artists(serv, m_name, limit, page);
}

pplx::task<std::vector<tag>> tag::get_top_tags(service& serv) {
    return serv.get("tag.gettoptags", {}, transform_select<std::vector<tag>>("toptags.tag.*"));
}

pplx::task<std::vector<track>> tag::get_top_tracks(service& serv, std::string_view name, std::optional<int> limit,
                                                   std::optional<int> page) {
    return serv.get("tag.gettoptracks",
                    detail::make_params(std::make_tuple("tag", name), std::make_tuple("limit", limit),
                                        std::make_tuple("page", page)),
                    transform_select<std::vector<track>>("toptracks.track.*"));
}

pplx::task<std::vector<track>> tag::get_top_tracks(service& serv, std::optional<int> limit,
                                                   std::optional<int> page) const {
    return get_top_tracks(serv, m_name, limit, page);
}

pplx::task<std::vector<artist>> tag::get_weekly_artist_chart(service& serv, std::string_view name,
                                                             std::optional<std::tuple<date_t, date_t>> date_range,
                                                             std::optional<int> limit) {
    std::optional<date_t> from, to;
    if(date_range)
        std::tie(from, to) = *date_range;

    return serv.get("tag.getweeklyartistchart",
                    detail::make_params(std::make_tuple("tag", name), std::make_tuple("from", from),
                                        std::make_tuple("to", to), std::make_tuple("limit", limit)),
                    transform_select<std::vector<artist>>("weeklyartistchart.artist.*"));
}

pplx::task<std::vector<artist>> tag::get_weekly_artist_chart(service& serv,
                                                             std::optional<std::tuple<date_t, date_t>> date_range,
                                                             std::optional<int> limit) const {
    return get_weekly_artist_chart(serv, m_name, date_range, limit);
}

pplx::task<std::vector<std::tuple<date_t, date_t>>> tag::get_weekly_chart_list(service& serv, std::string_view name) {
    auto transformer = [](jbson::document doc) {
        auto from = jbson::path_select(doc, "weeklychartlist.chart.*.from");
        auto to = jbson::path_select(doc, "weeklychartlist.chart.*.to");

        std::vector<std::tuple<date_t, date_t>> charts{};

        boost::transform(from, to, std::back_inserter(charts), [](auto&& from, auto&& to) {
            return std::make_tuple(deserialise<date_t>(from), deserialise<date_t>(to));
        });

        return charts;
    };
    return serv.get("tag.getweeklychartlist", detail::make_params(std::make_tuple("tag", name)), transformer);
}

pplx::task<std::vector<std::tuple<date_t, date_t>>> tag::get_weekly_chart_list(service& serv) const {
    return get_weekly_chart_list(serv, m_name);
}

pplx::task<std::vector<tag>> tag::search(service& serv, std::string_view name, std::optional<int> limit,
                                         std::optional<int> page) {
    return serv.get("tag.search", detail::make_params(std::make_tuple("tag", name), std::make_tuple("limit", limit),
                                                      std::make_tuple("page", page)),
                    transform_select<std::vector<tag>>("results.tagmatches.tag.*"));
}

pplx::task<std::vector<tag>> tag::search(service& serv, std::optional<int> limit, std::optional<int> page) const {
    return search(serv, m_name, limit, page);
}

} // namespace lastfm