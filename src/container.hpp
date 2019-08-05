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
    concept has_begin_c = requires (C& c)
    {
        { begin(c) } -> iterator_c;
    };

    template <typename C>
    concept has_end_c = requires (C& c)
	{
		end(c);
	};
}
template <detail::has_begin_c C>
using begin_t = decltype(begin(declval<C&>()));

template <detail::has_end_c C>
using end_t = decltype(end(declval<C&>()));

template <typename C>
constexpr bool is_container_v;
template <typename C>
constexpr bool is_container;
template <typename C>
concept container_c = detail::has_begin_c<C> && detail::has_end_c<C> && sentinel_c<end_t<C>, begin_t<C>>;

template <container_c C>
using container_base = base<begin_t<C>>;