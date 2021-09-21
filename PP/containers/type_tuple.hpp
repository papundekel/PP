#pragma once
#include "../get_type.hpp"
#include "../tuple/head_no_get.hpp"
#include "../tuple/recursive.hpp"
#include "../type_t.hpp"
#include "../value_t.hpp"

namespace PP
{
template <typename...>
struct type_tuple_t
{};
template <typename Head, typename... Rest>
struct type_tuple_t<Head, Rest...>
{
    type_tuple_t() = default;
    constexpr type_tuple_t(auto, auto...) noexcept
    {}

    constexpr auto head() const noexcept
    {
        return type<Head>;
    }
    constexpr auto head_element() const noexcept
    {
        return type<type_t<Head>>;
    }
    constexpr auto pred() const noexcept
    {
        return type_tuple_t<Rest...>{};
    }
    constexpr auto operator[](concepts::value auto i) const noexcept
    {
        return tuple::recursive(tuple::head_no_get, i, *this);
    }
};
template <typename... T>
type_tuple_t(type_t<T>...) -> type_tuple_t<T...>;

template <typename... T>
constexpr inline type_tuple_t<T...> type_tuple = {};

template <typename... T>
constexpr auto tuple_count_impl(type_tuple_t<T...>) noexcept
{
    return value<sizeof...(T)>;
}

PP_FUNCTOR(make_type_tuple, concepts::type auto... t)
{
    return type_tuple_t(to_type_t(t)...);
});

template <typename... T, typename... U>
constexpr auto type_tuple_concat(type_tuple_t<T...>,
                                 type_tuple_t<U...>) noexcept
{
    return type_tuple<T..., U...>;
}
}
