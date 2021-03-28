#pragma once
#include "same_except_ref.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T, typename U>
		concept same_except_cvref =
			same_except_ref<T,                U> ||
			same_except_ref<T, const          U> ||
			same_except_ref<T,       volatile U> ||
			same_except_ref<T, const volatile U>;

		template <typename T, typename U>
		concept different_except_cvref =
			different_except_ref<T,                U> &&
			different_except_ref<T, const          U> &&
			different_except_ref<T,       volatile U> &&
			different_except_ref<T, const volatile U>;
	}
}
