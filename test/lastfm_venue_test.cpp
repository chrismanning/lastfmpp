/**************************************************************************
**  Copyright (C) 2015 Christian Manning
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef MELOSIC_TEST_DATA_DIR
#error "MELOSIC_TEST_DATA_DIR define needed"
#endif

#include "catch.hpp"

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/range/size.hpp>

#include <jbson/json_reader.hpp>

#include <lastfm/venue.hpp>
#include <lastfm/detail/transform.hpp>

TEST_CASE("venues_deserialise") {
    boost::filesystem::path test_dir{MELOSIC_TEST_DATA_DIR};
    SECTION("get_info") {
        boost::filesystem::ifstream is{test_dir / "venue_search.json"};
        std::string venue_json;
        REQUIRE(std::getline(is, venue_json, static_cast<char>(EOF)));

        auto doc = jbson::read_json(venue_json);
        REQUIRE(boost::size(doc) == 1);

        std::vector<lastfm::venue> venues;
        REQUIRE_NOTHROW(venues = lastfm::transform_select<std::vector<lastfm::venue>>("results.venuematches.venue.*")(doc));

        REQUIRE(venues.size() == 50);
        CHECK(venues.front().location().city() == "Moscow");
        CHECK(venues.front().location().street() == u8"Ленинградский проспект 31, стр. 4 (м. Динамо)");
    }
}