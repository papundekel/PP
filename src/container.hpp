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
    concept x = requires (untype<C>& c)
    {
        requires iterator(type<decltype(begin(c))>{});
    };
}
template <typename C>
constexpr auto has_begin(C) { return dhas_begin::x<C>; }

namespace dhas_end
{
    template <typename C>
    concept x = requires (untype<C>& c)
	{
		end(c);
	};
}
template <typename C>
constexpr auto has_end(C) { return dhas_end::x<C>; }

template <typename C>
requires has_begin(C{})
constexpr auto begin_t(C c) { return typeof(begin(declval(c))); }
template <typename C>
requires has_end(C{})
constexpr auto end_t(C c) { return typeof(end(declval(c))); }

template <typename C>
constexpr auto container(C c) { return has_begin(c) && has_end(c) && sentinel(end_t(c), begin_t(c));}

template <typename C>
requires container(C{})
constexpr auto container_base(C c) { return base(begin_t(c)); }