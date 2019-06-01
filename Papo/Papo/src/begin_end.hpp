#pragma once
namespace detail
{
	template <typename T, typename = void>
	constexpr bool _has_begin_end = false;

	template <typename T>
	constexpr bool _has_begin_end<T, enable_if<
		is_iterator<decltype(declval<T&>().begin())>&&
		is_iterator<decltype(declval<T&>().end())>&&
		is_iterator<decltype(declval<const T&>().begin())>&&
		is_iterator<decltype(declval<const T&>().end())>
	>> = true;
}

template <typename container, typename =
enable_if<detail::_has_begin_end<container>>>
constexpr auto begin(container& c)
{
	return c.begin();
}
template <typename container, typename =
enable_if<detail::_has_begin_end<container>>>
constexpr auto end(container& c)
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