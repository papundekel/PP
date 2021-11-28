#pragma once
#include <PP/same.hpp>

namespace PP
{
namespace concepts
{
// clang-format off
		template <typename T, typename U>
		concept same_except_ref =
			same<T, U>
		||	same<T, U&>
		||	same<T, U&&>;

		template <typename T, typename U>
		concept different_except_ref =
			different<T, U>
		&&	different<T, U&>
		&&	different<T, U&&>;
// clang-format on
}
}
