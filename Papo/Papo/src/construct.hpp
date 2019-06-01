#pragma once
#include "iterator.hpp"
#include "is_arithmetic.hpp"
#include "remove_reference.hpp"
#include "forward.hpp"
#include "get_address.hpp"

template <iterator it, typename U>
void construct(it where, U&& value)
{
	using base = base_t<it>;

	if constexpr (is_arithmetic<base>)
		*where = forward<U>(value);
	else
		new (get_address(where)) base(forward<U>(value));
}