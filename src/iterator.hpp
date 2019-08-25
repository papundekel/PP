#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "assignable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"
#include "value_t_operators.hpp"

namespace diterator
{
	template <typename T>
	concept x = requires (T i)
	{
		{ *i } -> auto&&;
	};
	template <typename T>
	constexpr bool y = AND<equatable<T>, incrementable<T>, value_t<x<T>>>::v;
}

template <typename T>
using iterator = value_t<diterator::y<T>>;

template <typename I>
requires iterator<I>::v
using base = remove_reference<decltype(*declval<I>())>;