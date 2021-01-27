#pragma once
#include "add_pointer.hpp"
#include "concepts/array.hpp"
#include "concepts/function.hpp"
#include "functional/caller.hpp"
#include "functional/functor.hpp"
#include "remove_extent.hpp"
#include "remove_reference.hpp"

namespace PP
{
	constexpr inline auto decay = caller([](concepts::type auto type)
	{
		constexpr auto T = PP_COPY_TYPE(type);

		if constexpr (is_array(T))
			return add_pointer | remove_extent;
		else if constexpr (is_function(T))
			return add_pointer;
		else
			return remove_cv;
	}) | remove_reference;
}
