#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"

namespace diterator
{
	template <typename T>
	constexpr auto x = requires (T i)
	{
		{ *i } -> auto&;
	};
}

template <typename T>
constexpr auto iterator = diterator::x<T>;

template <typename I>
requires iterator<I>
using base = remove_reference<decltype(*declval<I>())>;