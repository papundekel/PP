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
namespace detail::has_begin
{
    template <typename C>
    concept x = requires (C& c)
    {
        requires iterator<decltype(begin(c))>::v;
    };
}
template <typename C>
struct has_begin : val<detail::has_begin::x<C>> {};

namespace detail::has_end
{
    template <typename C>
    concept x = requires (C& c)
	{
		end(c);
	};
}
template <typename C>
struct has_end : val<detail::has_end::x<C>> {};

template <typename C>
requires has_begin<C>::v
using begin_t = decltype(begin(declval<C&>()));
template <typename C>
requires has_end<C>::v
using end_t = decltype(end(declval<C&>()));

template <typename C>
using container = val<has_begin<C>::v && has_end<C>::v && sentinel<end_t<C>, begin_t<C>>::v>;

template <typename C>
requires container<C>::v
using container_base = base<begin_t<C>>;