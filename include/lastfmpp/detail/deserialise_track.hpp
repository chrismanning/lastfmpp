/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DESERIALISE_TRACK
#define LASTFM_DESERIALISE_TRACK

#include <jbson/element.hpp>

#include <lastfmpp/track.hpp>
#include <lastfmpp/detail/deserialise_mbid.hpp>
#include <lastfmpp/detail/deserialise_wiki.hpp>
#include <lastfmpp/detail/deserialise_ext.hpp>
#include <lastfmpp/detail/deserialise_album.hpp>
#include <lastfmpp/detail/deserialise_tag.hpp>
#include <lastfmpp/detail/deserialise_artist.hpp>

namespace lastfmpp {

template <typename Container> void value_get(const jbson::basic_element<Container>& tag_elem, track& var) {
    auto doc = jbson::get<jbson::element_type::document_element>(tag_elem);
    for(auto&& elem : doc) {
        if(elem.name() == "name") {
            var.name(jbson::get<jbson::element_type::string_element>(elem));
        } else if(elem.name() == "url") {
            var.url(jbson::get<uri_t>(elem));
        } else if(elem.name() == "artist") {
            var.artist(jbson::get<artist>(elem));
        } else if(elem.name() == "album") {
            var.album(jbson::get<album>(elem));
            if(auto num = vector_to_optional(jbson::path_select(jbson::get<jbson::document>(elem), "@attr.position"))) {
                auto str = jbson::get<jbson::element_type::string_element>(*num);
                var.tracknumber(std::strtol(str.data(), nullptr, 10));
            }
        } else if(elem.name() == "toptags" || elem.name() == "tags") {
            if(elem.type() == jbson::element_type::document_element) {
                for(auto&& e : jbson::get<jbson::element_type::document_element>(elem))
                    if(e.name() == "tag")
                        var.top_tags(jbson::get<std::vector<tag>>(e));
            } else {
                var.top_tags(jbson::get<std::vector<tag>>(elem));
            }
        } else if(elem.name() == "similar") {
            if(elem.type() == jbson::element_type::document_element) {
                for(auto&& e : jbson::get<jbson::element_type::document_element>(elem))
                    if(e.name() == "track")
                        var.similar(jbson::get<std::vector<track>>(e));
            } else {
                var.similar(jbson::get<std::vector<track>>(elem));
            }
        } else if(elem.name() == "duration") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.duration(std::chrono::milliseconds(std::strtol(str.data(), nullptr, 10)));
        } else if(elem.name() == "listeners") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.listeners(std::strtol(str.data(), nullptr, 10));
        } else if(elem.name() == "playcount") {
            auto str = jbson::get<jbson::element_type::string_element>(elem);
            var.plays(std::strtol(str.data(), nullptr, 10));
        } else if(elem.name() == "streamable") {
            if(elem.type() == jbson::element_type::string_element)
                var.streamable(jbson::get<jbson::element_type::string_element>(elem) == "1");
            else if(elem.type() == jbson::element_type::document_element) {
                if(auto num = vector_to_optional(jbson::path_select(jbson::get<jbson::document>(elem), "#text")))
                    var.streamable(jbson::get<jbson::element_type::string_element>(*num) == "1");
            }
        } else if(elem.name() == "wiki") {
            var.wiki(jbson::get<wiki>(elem));
        } else if(elem.name() == "mbid") {
            var.mbid(jbson::get<mbid_t>(elem));
        }
    }
}

} // namespace lastfmpp

#endif // LASTFM_DESERIALISE_TRACK

