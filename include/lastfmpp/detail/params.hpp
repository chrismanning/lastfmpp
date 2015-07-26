/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_PARAMS
#define LASTFM_PARAMS

#include <sstream>

#include <boost/uuid/uuid_io.hpp>
#include <boost/hana/ext/std.hpp>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/date.hpp>
#include <lastfmpp/params.hpp>
#include <lastfmpp/detail/hana_optional.hpp>

namespace lastfmpp::detail {

namespace hana = boost::hana;

struct to_string_ {
    inline std::string operator()(date_t t) const {
        auto time = date_t::clock::to_time_t(t);
        std::stringstream ss{};
        ss << std::put_time(std::gmtime(&time), "%a, %d %b %Y %H:%M:%S");
        return ss.str();
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

struct make_params_ {
    template <typename... PairT> params_t operator()(PairT&&... optional_params) const {
        params_t params{};
        for(auto&& param : {make_param(std::forward<PairT>(optional_params))...}) {
            hana::unpack(std::forward<decltype(param)>(param), [&](auto&& name, auto&& maybe) {
                if(maybe && !maybe->empty())
                    params.emplace_back(std::move(name), *std::move(maybe));
            });
        }
        return params;
    }

  private:
    template <typename PairT> static std::tuple<std::string, std::optional<std::string>> make_param(PairT&& t) {
        return hana::unpack(std::forward<PairT>(t), [](auto&& a, auto&& b) {
            return std::make_tuple(std::string{a},
                                   hana::transform(hana::flatten(std::make_optional(b)), to_string_{}));
        });
    }
};

constexpr auto make_params = make_params_{};

} // namespace lastfmpp::detail

#endif // LASTFM_PARAMS
