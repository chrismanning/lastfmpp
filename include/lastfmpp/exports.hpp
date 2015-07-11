/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_EXPORTS_HPP
#define LASTFM_EXPORTS_HPP

#include <boost/config.hpp>

#ifdef LASTFM_EXPORTS
#define LASTFM_EXPORT BOOST_SYMBOL_EXPORT
#else
#define LASTFM_EXPORT BOOST_SYMBOL_IMPORT
#endif

#ifndef _WIN32
#define LASTFM_LOCAL [[gnu::visibility("hidden")]]
#else
#define LASTFM_LOCAL
#endif

#endif // LASTFM_EXPORTS_HPP
