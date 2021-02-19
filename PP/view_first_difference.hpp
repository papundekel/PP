#pragma once
#include "functional/applier.hpp"
#include "functional/apply_partially.hpp"
#include "functional/compose.hpp"
#include "functional/operators.hpp"
#include "view_find.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_first_difference = view_find * *neq | zip_view_pack;
}
