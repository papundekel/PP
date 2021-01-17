#pragma once
#include "../add_reference.hpp"
#include "../get_type.hpp"
#include "../remove_reference.hpp"

namespace PP
{
	constexpr decltype(auto) move(auto&& x) noexcept
	{
		return static_cast<PP_GET_TYPE(!PP_DECLTYPE(x) + rvalue_tag)>(x);
	}
}
