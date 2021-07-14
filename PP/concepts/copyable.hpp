#pragma once
#include "../declval_impl.hpp"
#include "../remove_reference_impl.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept copyable = requires
		{
			[](remove_reference_impl<T>)
			{
			}(declval_impl<T>());
		};
	}
}
