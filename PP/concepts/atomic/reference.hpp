#pragma once
#include "../../add_reference.hpp"
#include "../../conjunction.hpp"
#include "../same.hpp"
#include "referencable.hpp"

namespace PP
{
constexpr inline auto is_reference =
	is_referencable && functor(
						   [](concepts::type auto t)
						   {
							   return t + add_rvalue_tag == t;
						   });
}