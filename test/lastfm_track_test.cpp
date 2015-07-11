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

#include <lastfmpp/track.hpp>
#include <lastfmpp/tag.hpp>
#include <lastfmpp/detail/deserialise_track.hpp>

TEST_CASE("track_deserialise") {
    boost::filesystem::path test_dir{LASTFMPP_TEST_DATA_DIR};
    SECTION("get_info") {
        boost::filesystem::ifstream is{test_dir / "track_getinfo.json"};
        std::string track_json;
        REQUIRE(std::getline(is, track_json, static_cast<char>(EOF)));

        auto doc = jbson::read_json(track_json);
        REQUIRE(boost::size(doc) == 1);

        auto track_elem = *doc.begin();

        lastfmpp::track track;
        REQUIRE_NOTHROW(track = jbson::get<lastfmpp::track>(track_elem));

        CHECK(track.name() == "Master of Puppets");
        CHECK(track.artist().name() == "Metallica");
        CHECK(track.album().name() == "Master of Puppets");
        CHECK(track.tracknumber() == 2);
        REQUIRE(track.top_tags().size() > 0);
        CHECK(track.top_tags().front().name() == "thrash metal");
        CHECK_FALSE(track.streamable());
        CHECK(track.wiki().summary().size() > 0);
    }
}
