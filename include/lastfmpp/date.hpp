/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_DATE_HPP
#define LASTFM_DATE_HPP

#include <chrono>

namespace lastfmpp {

using date_t = std::chrono::system_clock::time_point;

} // namespace lastfmpp

#endif // LASTFM_DATE_HPP

