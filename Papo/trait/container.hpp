#pragma once
#include "sentinel.hpp"
#include "type.hpp"
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
namespace dhas_begin
{
    template <typename C>
    constexpr auto x = requires (C c)
    {
        requires iterator<decltype(begin(c))>;
    };
}
template <typename C>
constexpr auto has_begin = dhas_begin::x<C>;

namespace dhas_end
{
    template <typename C>
     constexpr auto x = requires (C c)
	{
		end(c);
	};
}
template <typename C>
constexpr auto has_end = dhas_end::x<C>;

template <typename C>
requires has_begin<C>
using begin_t = decltype(begin(declval<C>()));
template <typename C>
requires has_end<C>
using end_t = decltype(end(declval<C>()));

template <typename C>
constexpr auto container = has_begin<C> && has_end<C> && sentinel<end_t<C>, begin_t<C>>;

template <typename C>
requires container<C>
using container_base = base<begin_t<C>>;