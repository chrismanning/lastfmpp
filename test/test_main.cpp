/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#include <boost/config.hpp>
#include <boost/locale.hpp>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char** argv) {
    boost::locale::generator gen;
    std::locale::global(gen("en_GB.UTF-8"));

    return Catch::Session().run(argc, argv);
}
