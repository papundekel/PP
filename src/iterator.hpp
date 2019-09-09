#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"
#include "val_operators.hpp"

namespace diterator
{
	template <typename T>
	concept x = requires (T i)
	{
		{ *i } -> auto&&;
	};
	template <typename T>
	// using y = AND<>; causes weird recursive error
	constexpr bool y = AND<equatable<T>, incrementable<T>, val<x<T>>>::v;
}

template <typename T>
using iterator = val<diterator::y<T>>;

template <typename I>
requires iterator<I>::v
using base = remove_reference<decltype(*declval<I>())>;