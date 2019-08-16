#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "assignable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"

namespace diterator
{
	template <typename T>
	concept x = requires (T i)
	{
		{ *i } -> auto&&;
	};
}
template <typename T>
struct iterator : value_t<equatable<T>::v && incrementable<T>::v && diterator::x<T>> {};

template <typename I>
requires iterator<I>::v
using base = remove_reference<decltype(*declval<I>())>;