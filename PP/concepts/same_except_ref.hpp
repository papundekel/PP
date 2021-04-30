#pragma once
#include "same.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T, typename U>
		concept same_except_ref = same<T, U> || same<T, U&> || same<T, U&&>;

		template <typename T, typename U>
		concept different_except_ref =
			different<T, U>&& different<T, U&>&& different<T, U&&>;
	}
}
