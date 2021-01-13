#pragma once
#include "remove_cv.hpp"
#include "remove_reference.hpp"
#include "functional/compose.hpp"

namespace PP
{
	constexpr inline auto remove_cvref = remove_cv | remove_reference;

	constexpr auto operator~(type_wrap auto t) noexcept
	{
		return remove_cvref(t);
	}
}
