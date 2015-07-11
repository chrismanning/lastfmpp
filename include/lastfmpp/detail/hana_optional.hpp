/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_HANA_OPTIONAL
#define LASTFM_HANA_OPTIONAL

#include <experimental/optional>

#include <boost/hana.hpp>

namespace std {
using namespace experimental;
}

namespace boost::hana {

    namespace ext::std {
        struct Optional;
    }

    template <typename T> struct datatype<::std::optional<T>> { using type = ext::std::Optional; };

    template <> struct lift_impl<ext::std::Optional> {
        template <typename X> static constexpr decltype(auto) apply(X&& x) {
            return std::make_optional(std::forward<X>(x));
        }
    };

    template <> struct ap_impl<ext::std::Optional> {
        template <typename F, typename... X>
        static constexpr auto apply_impl(std::false_type, F&& f, X&&... x)
            -> decltype(std::make_optional((*f)(x.value()...))) {
            if(f && (... && x))
                return std::make_optional((*f)(x.value()...));
            return std::nullopt;
        }
        template <typename F, typename... X> static constexpr void apply_impl(std::true_type, F&& f, X&&... x) {
            if(f && (... && x))
                (*f)(x.value()...);
        }
        template <typename F, typename... X> static constexpr decltype(auto) apply(F&& f, X&&... x) {
            return apply_impl(std::is_void<decltype((*f)(x.value()...))>{}, std::forward<F>(f), std::forward<X>(x)...);
        }
    };

    template <> struct transform_impl<ext::std::Optional> : Applicative::transform_impl<ext::std::Optional> {};

    template <> struct flatten_impl<ext::std::Optional> {
        template <typename X> static constexpr decltype(auto) apply(std::optional<std::optional<X>>&& x) {
            return x ? *std::move(x) : std::nullopt;
        }

        template <typename X> static constexpr decltype(auto) apply(std::optional<std::optional<X>>& x) {
            return x ? *x : std::nullopt;
        }

        template <typename X> static constexpr decltype(auto) apply(const std::optional<std::optional<X>>& x) {
            return x ? *x : std::nullopt;
        }

        template <typename X> static constexpr decltype(auto) apply(X&& x) {
            return std::forward<X>(x);
        }
    };
}

#endif // LASTFM_HANA_OPTIONAL
