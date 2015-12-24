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

namespace boost::hana {

    namespace ext::std::experimental {
        struct Optional;
    }

    template <typename T> struct datatype<::std::experimental::optional<T>> {
        using type = ext::std::experimental::Optional;
    };

    template <> struct lift_impl<ext::std::experimental::Optional> {
        template <typename X> static constexpr decltype(auto) apply(X&& x) {
            return std::experimental::make_optional(std::forward<X>(x));
        }
    };

    template <> struct ap_impl<ext::std::experimental::Optional> {
        template <typename F, typename... X>
        static constexpr auto apply_impl(std::false_type, F&& f, X&&... x)
            -> decltype(std::experimental::make_optional((*f)(x.value()...))) {
            if(f && (... && x))
                return std::experimental::make_optional((*f)(x.value()...));
            return std::experimental::nullopt;
        }
        template <typename F, typename... X> static constexpr void apply_impl(std::true_type, F&& f, X&&... x) {
            if(f && (... && x))
                (*f)(x.value()...);
        }
        template <typename F, typename... X> static constexpr decltype(auto) apply(F&& f, X&&... x) {
            return apply_impl(std::is_void<decltype((*f)(x.value()...))>{}, std::forward<F>(f), std::forward<X>(x)...);
        }
    };

    template <>
    struct transform_impl<ext::std::experimental::Optional>
        : Applicative::transform_impl<ext::std::experimental::Optional> {};

    template <> struct flatten_impl<ext::std::experimental::Optional> {
        template <typename X>
        static constexpr decltype(auto) apply(std::experimental::optional<std::experimental::optional<X>>&& x) {
            return x ? *std::move(x) : std::experimental::nullopt;
        }

        template <typename X>
        static constexpr decltype(auto) apply(std::experimental::optional<std::experimental::optional<X>>& x) {
            return x ? *x : std::experimental::nullopt;
        }

        template <typename X>
        static constexpr decltype(auto) apply(const std::experimental::optional<std::experimental::optional<X>>& x) {
            return x ? *x : std::experimental::nullopt;
        }

        template <typename X> static constexpr decltype(auto) apply(X&& x) {
            return std::forward<X>(x);
        }
    };

    template <> struct concat_impl<ext::std::experimental::Optional> {
        template <typename X, typename Y> static constexpr auto apply(X&& x, Y&& y) {
            return x ? std::forward<X>(x) : std::forward<Y>(y);
        }
    };

    template <> struct empty_impl<ext::std::experimental::Optional> {
        static constexpr auto apply() {
            return std::experimental::nullopt;
        }
    };

    template <> struct find_if_impl<ext::std::experimental::Optional> {
        template <typename M, typename Pred> static constexpr decltype(auto) apply(M&& m, Pred&& pred) {
            return hana::any_of(std::forward<M>(m), std::forward<Pred>(pred)) ? hana::just(*m) : hana::nothing;
        }
    };

    template <> struct any_of_impl<ext::std::experimental::Optional> {
        template <typename M, typename Pred> static constexpr decltype(auto) apply(M&& m, Pred&& p) {
            return m && p(*m);
        }
    };
}

#endif // LASTFM_HANA_OPTIONAL
