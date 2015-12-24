/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <catch.hpp>

#include <boost/range/algorithm/lexicographical_compare.hpp>

#include <lastfmpp/detail/params.hpp>
using namespace lastfmpp;
using namespace lastfmpp::detail;

template <typename T> std::experimental::optional<T> nullopt = std::experimental::nullopt;

TEST_CASE("make_params") {
    SECTION("basic") {
        auto params = make_params(std::make_pair("a", "b"), std::make_pair("c", 3));
        auto expected = params_t{std::make_pair("a", "b"), std::make_pair("c", "3")};
        REQUIRE(params == expected);
    }

    SECTION("optional null") {
        auto params = make_params(std::make_pair("a", "b"), std::make_pair("c", 3), std::make_pair("d", nullopt<int>));
        auto expected = params_t{std::make_pair("a", "b"), std::make_pair("c", "3")};
        REQUIRE(params == expected);
    }

    SECTION("optional non-null") {
        auto params = make_params(std::make_pair("a", "b"), std::make_pair("c", 3),
                                  std::make_pair("d", std::experimental::make_optional(321)));
        auto expected = params_t{std::make_pair("a", "b"), std::make_pair("c", "3"), std::make_pair("d", "321")};
        REQUIRE(params == expected);
    }

    SECTION("optional non-null & null") {
        auto params =
            make_params(std::make_pair("a", "b"), std::make_pair("c", nullopt<std::experimental::string_view>),
                        std::make_pair("d", std::experimental::make_optional(321)));
        auto expected = params_t{std::make_pair("a", "b"), std::make_pair("d", "321")};
        REQUIRE(params == expected);
    }
}
