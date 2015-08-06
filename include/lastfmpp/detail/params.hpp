/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_PARAMS
#define LASTFM_PARAMS

#include <sstream>
#include <type_traits>

#include <boost/uuid/uuid_io.hpp>
#include <boost/hana.hpp>
#include <boost/hana/ext/std.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/date.hpp>
#include <lastfmpp/params.hpp>
#include <lastfmpp/detail/hana_optional.hpp>

namespace lastfmpp::detail {

namespace hana = boost::hana;

struct _to_string {
    inline std::string operator()(date_t t) const {
        auto time = date_t::clock::to_time_t(t);
        std::stringstream ss{};
        ss << std::put_time(std::gmtime(&time), "%a, %d %b %Y %H:%M:%S");
        return ss.str();
    }
    inline std::string operator()(const char* s) const {
        return std::string{s};
    }
    inline std::string operator()(std::string_view s) const {
        return s.to_string();
    }
    inline std::string operator()(std::string s) const {
        return std::move(s);
    }
    template <typename N> inline std::string operator()(N&& i) const {
        using ::std::to_string;
        return to_string(i);
    }
};

struct _not_empty {
    template <typename T> constexpr bool operator()(T&& t) const {
        return !t.empty();
    }
};

constexpr _not_empty not_empty{};

struct _bifunctor {
    template <typename PairT, typename F, typename G>
    constexpr auto operator()(PairT&& pair, F&& f, G&& g) const {
        return hana::unpack(pair, hana::lockstep(hana::make<hana::datatype_t<std::decay_t<PairT>>>)(f, g));
    }
};

constexpr auto bitransform = _bifunctor{};

struct _bifunctor_first {
    template <typename PairT, typename F>
    constexpr auto operator()(PairT&& pair, F&& f) const {
        return bitransform(std::forward<PairT>(pair), std::forward<F>(f), hana::id);
    }
};

constexpr auto bifirst = _bifunctor_first{};

struct _bifunctor_second {
    template <typename PairT, typename F>
    constexpr auto operator()(PairT&& pair, F&& f) const {
        return bitransform(std::forward<PairT>(pair), hana::id, std::forward<F>(f));
    }
};

constexpr auto bisecond = _bifunctor_second{};

struct _make_params {
    template <typename... PairT> params_t operator()(PairT&&... optional_params) const {
        using namespace boost::adaptors;

        auto predicate = hana::compose(hana::partial(hana::flip(hana::any_of), not_empty), hana::at_c<1>);
        auto params_list = {make_param(std::forward<PairT>(optional_params))...};

        auto transformer = hana::partial(hana::flip(bisecond), *hana::_);
        auto transformed_params = params_list | filtered(predicate) | transformed(transformer);

        return {std::begin(transformed_params), std::end(transformed_params)};
    }

  private:
    template <typename PairT> static std::tuple<std::string, std::optional<std::string>> make_param(PairT&& t) {
        return hana::unpack(std::forward<PairT>(t), [](auto&& a, auto&& b) {
            return std::make_tuple(std::string{a},
                                   hana::transform(hana::flatten(std::make_optional(b)), _to_string{}));
        });
    }
};

constexpr auto make_params = _make_params{};

} // namespace lastfmpp::detail

#endif // LASTFM_PARAMS
