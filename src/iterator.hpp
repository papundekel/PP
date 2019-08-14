#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "assignable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"

namespace concepts
{
	template <typename T>
	concept iterator = ::equatable<T>::v && ::incrementable<T>::v &&
	requires (T i)
	{
		{ *i } -> auto&&;
	};
}
template <typename T>
struct iterator : value_t<concepts::iterator<T>> {};

template <typename I>
requires iterator<I>::v
using base = remove_reference<decltype(*declval<I>())>;