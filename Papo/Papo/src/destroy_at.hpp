#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "is_arithmetic.hpp"
#include "base_type.hpp"

template <typename it>
enable_if<is_iterator<it>,
void> destroy_at(it where)
{
	using base = base_type<it>;

	if constexpr (!is_arithmetic<base> && !is_pointer<base>)
		where->~base();
}