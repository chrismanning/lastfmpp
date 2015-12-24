/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_TRANSFORM
#define LASTFM_TRANSFORM

#include <algorithm>
#include <type_traits>

#include <jbson/element.hpp>
#include <jbson/document.hpp>
#include <jbson/path.hpp>

namespace lastfmpp {

namespace detail {

template <typename T> struct deserialise_ {
    template <typename ElemT> T operator()(ElemT&& elem) const {
        return jbson::get<T>(elem);
    }
};

} // namespace detail

template <typename T> constexpr auto deserialise = detail::deserialise_<T>{};

namespace detail {

template <typename T> struct _convert {
    template <typename U> constexpr T operator()(U&& u) const {
        return static_cast<T>(u);
    }
};

} // namespace detail

template <typename T> constexpr auto convert = detail::_convert<T>{};

namespace detail {

struct transform_copy_ {
    template <typename V, typename F> auto operator()(V&& v, F&& f) const {
        using U = std::remove_cv_t<std::remove_reference_t<decltype(f(*v.begin()))>>;
        using Alloc = typename std::remove_reference_t<V>::allocator_type;
        using NewAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<U>;
        std::vector<U, NewAlloc> result;
        result.reserve(v.size());

        std::transform(move_begin(v), move_end(v), std::back_inserter(result), std::forward<F>(f));
        return result;
    }

  private:
    template <typename V>
    using iterator_type = std::conditional_t<std::is_rvalue_reference<V>::value,
                                             std::move_iterator<decltype(std::begin(std::declval<V>()))>,
                                             decltype(std::begin(std::declval<V>()))>;

    template <typename V> static auto move_begin(V&& v) {
        return iterator_type<V>{std::begin(v)};
    }

    template <typename V> static auto move_end(V&& v) {
        return iterator_type<V>{std::end(v)};
    }
};

} // namespace detail

constexpr auto transform_copy = detail::transform_copy_{};

namespace detail {

struct vector_to_optional_ {
    template <typename T, typename... Args>
    std::experimental::optional<T> operator()(std::vector<T, Args...>&& vec) const {
        return vec.empty() ? std::experimental::nullopt : std::experimental::make_optional(std::move(vec.front()));
    }

    template <typename T, typename... Args>
    std::experimental::optional<T> operator()(const std::vector<T, Args...>& vec) const {
        return vec.empty() ? std::experimental::nullopt : std::experimental::make_optional(vec.front());
    }
};

} // namespace detail

constexpr auto vector_to_optional = detail::vector_to_optional_{};

namespace detail {

template <typename T> struct transform_select_ {
    auto operator()(std::experimental::string_view path) const {
        return [path = path.to_string()](jbson::document doc) {
            if(auto elem = vector_to_optional(jbson::path_select(std::move(doc), path))) {
                return jbson::get<T>(*elem);
            }
            throw std::runtime_error("invalid response");
        };
    }
};

template <typename T> struct transform_select_<std::vector<T>> {
    auto operator()(std::experimental::string_view path) const {
        return [path = path.to_string()](jbson::document doc) {
            auto elems = jbson::path_select(std::move(doc), path);
            return transform_copy(elems, deserialise<T>);
        };
    }
};

} // namespace detail

template <typename T> constexpr auto transform_select = detail::transform_select_<T>{};

namespace detail {
struct _ignore_impl {
    template <typename... Args> constexpr void operator()(Args&&...) const {
    }
};
constexpr _ignore_impl ignore{};
}

} // namespace lastfm

#endif // LASTFM_TRANSFORM
