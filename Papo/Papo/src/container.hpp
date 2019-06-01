#pragma once
#include "sentinel.hpp"
#include "declval.hpp"
namespace detail
{
    template <typename C>
    concept container_helper = requires(C c)
    {
        c.begin();
        c.end();
    };
}
template <detail::container_helper C>
constexpr auto begin(C& c)
{
	return c.begin();
}
template <detail::container_helper C>
constexpr auto end(C& c)
{
	return c.end();
}

template <typename T, size_t size>
constexpr auto begin(T(&arr)[size])
{
	return arr;
}
template <typename T, size_t size>
constexpr auto end(T(&arr)[size])
{
	return arr + size;
}
namespace detail
{
    template <typename C>
    concept has_begin = requires(C& c)
    {
        { ::begin(c) } -> iterator;
    };

    template <typename C>
    concept has_end = requires(C& c) { end(c); };
}
template <detail::has_begin C>
using begin_t = decltype(::begin(declval<C&>()));

template <detail::has_end C>
using end_t = decltype(::end(declval<C&>()));

template <typename C>
concept container = detail::has_begin<C> && detail::has_end<C> && sentinel<end_t<C>, begin_t<C>>;
