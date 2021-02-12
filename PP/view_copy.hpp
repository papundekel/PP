#pragma once
#include "functional/apply_partially.hpp"
#include "functional/operators.hpp"
#include "view_zip_with_pack.hpp"

namespace PP
{
	constexpr inline auto view_copy = zip_with_pack * asg;
}
