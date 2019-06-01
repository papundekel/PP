#pragma once
#include "void_v.hpp"
#include "is_iterator.hpp"
template <typename T, typename = void_t<>>
constexpr bool is_iterator_bi = false;

template <typename T>
constexpr bool is_iterator_bi<T, void_t<decltype(
	--declval<T&>()
)>> = is_iterator<T>;

template <typename it>
enable_if<is_iterator_bi<it>,
it> operator--(it& i, int)
{
	auto temp = i;
	--i;
	return temp;
}