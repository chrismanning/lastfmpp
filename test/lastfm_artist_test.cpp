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

#include <lastfmpp/artist.hpp>
#include <lastfmpp/tag.hpp>
#include <lastfmpp/detail/deserialise_artist.hpp>

TEST_CASE("artist_deserialise") {
    boost::filesystem::path test_dir{LASTFMPP_TEST_DATA_DIR};
    SECTION("get_info") {
        boost::filesystem::ifstream is{test_dir / "artist_getinfo.json"};
        std::string artist_json;
        REQUIRE(std::getline(is, artist_json, static_cast<char>(EOF)));

        auto doc = jbson::read_json(artist_json);
        REQUIRE(boost::size(doc) == 1);

        auto artist_elem = *doc.begin();

        lastfmpp::artist artist;
        REQUIRE_NOTHROW(artist = jbson::get<lastfmpp::artist>(artist_elem));

        CHECK(artist.name() == "Metallica");
        CHECK(artist.top_tags().front().name() == "thrash metal");
        CHECK_FALSE(artist.streamable());
        CHECK(artist.wiki().summary().size() > 0);
        REQUIRE(artist.images().size() > 0);
        CHECK(artist.images().back().size() != lastfmpp::image_size::small);
    }
}
