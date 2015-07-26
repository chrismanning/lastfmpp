/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_PARAMS_HPP
#define LASTFM_PARAMS_HPP

#include <vector>
#include <tuple>
#include <string>

namespace lastfmpp {

using params_t = std::vector<std::tuple<std::string, std::string>>;

} // namespace lastfmpp

#endif // LASTFM_PARAMS_HPP
