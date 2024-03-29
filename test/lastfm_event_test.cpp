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

#include <lastfmpp/event.hpp>
#include <lastfmpp/artist.hpp>
#include <lastfmpp/detail/deserialise_event.hpp>

TEST_CASE("album_deserialise") {
    boost::filesystem::path test_dir{LASTFMPP_TEST_DATA_DIR};
    SECTION("get_info") {
        boost::filesystem::ifstream is{test_dir / "event_getinfo.json"};
        std::string event_json;
        REQUIRE(std::getline(is, event_json, static_cast<char>(EOF)));

        auto doc = jbson::read_json(event_json);
        REQUIRE(boost::size(doc) == 1);

        auto event_elem = *doc.begin();

        lastfmpp::event event;
        try {
            /*REQUIRE_NOTHROW*/ (event = jbson::get<lastfmpp::event>(event_elem));
        } catch(...) {
            std::clog << boost::current_exception_diagnostic_information();
            CHECK(false);
        }

        CHECK(event.name() == "Philip Glass");
        REQUIRE(event.artists().size() > 0);
        CHECK(event.artists().front().name() == "Philip Glass");
        CHECK(event.images().size() > 0);
        CHECK(event.venue().name() == "Barbican Centre");
        CHECK(event.venue().images().size() > 0);
    }
}
