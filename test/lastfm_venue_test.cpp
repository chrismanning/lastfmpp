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

#include <lastfmpp/venue.hpp>
#include <lastfmpp/detail/transform.hpp>
#include <lastfmpp/detail/deserialise_venue.hpp>

TEST_CASE("venues_deserialise") {
    boost::filesystem::path test_dir{LASTFMPP_TEST_DATA_DIR};
    SECTION("get_info") {
        boost::filesystem::ifstream is{test_dir / "venue_search.json"};
        std::string venue_json;
        REQUIRE(std::getline(is, venue_json, static_cast<char>(EOF)));

        auto doc = jbson::read_json(venue_json);
        REQUIRE(boost::size(doc) == 1);

        std::vector<lastfmpp::venue> venues;
        REQUIRE_NOTHROW(venues = lastfmpp::transform_select<std::vector<lastfmpp::venue>>("results.venuematches.venue.*")(doc));

        REQUIRE(venues.size() == 50);
        CHECK(venues.front().location().city() == "Moscow");
        CHECK(venues.front().location().street() == u8"Ленинградский проспект 31, стр. 4 (м. Динамо)");
    }
}
