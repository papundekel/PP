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
	concept x = requires (T i)
	{
		{ *i } -> auto&&;
	};
}

template <typename T>
constexpr auto iterator(T) { return diterator::x<untype<T>>;}

template <typename I>
requires iterator(I{})
constexpr auto base(I i) { return remove_reference(typeof(*declval(i))); }