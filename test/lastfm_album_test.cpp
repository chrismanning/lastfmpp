/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFMPP_TEST_DATA_DIR
#error "LASTFMPP_TEST_DATA_DIR define needed"
#endif

#include "catch.hpp"

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/range/size.hpp>

#include <jbson/json_reader.hpp>

#include <lastfmpp/album.hpp>
#include <lastfmpp/track.hpp>
#include <lastfmpp/tag.hpp>
#include <lastfmpp/detail/deserialise_album.hpp>

TEST_CASE("album_deserialise") {
    boost::filesystem::path test_dir{LASTFMPP_TEST_DATA_DIR};
    SECTION("get_info") {
        boost::filesystem::ifstream is{test_dir / "album_getinfo.json"};
        std::string album_json;
        REQUIRE(std::getline(is, album_json, static_cast<char>(EOF)));

        auto doc = jbson::read_json(album_json);
        REQUIRE(boost::size(doc) == 1);

        auto album_elem = *doc.begin();

        lastfmpp::album album;
        REQUIRE_NOTHROW(album = jbson::get<lastfmpp::album>(album_elem));

        CHECK(album.name() == "Master of Puppets");
        CHECK(album.artist().name() == "Metallica");
        REQUIRE(album.top_tags().size() > 0);
        CHECK(album.top_tags().front().name() == "thrash metal");
        CHECK_FALSE(album.streamable());
        CHECK(album.tracks().size() > 0);
        REQUIRE(album.images().size() > 0);
        CHECK(album.images().back().size() != lastfmpp::image_size::small);
    }
}
