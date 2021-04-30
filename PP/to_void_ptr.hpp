#pragma once
#include "overloaded.hpp"

namespace PP
{
	constexpr inline auto to_void_ptr = make_overloaded_pack(
		[](auto* p) -> void*
		{
			return p;
		},
		[](const auto* p) -> const void*
		{
			return p;
		},
		[](volatile auto* p) -> volatile void*
		{
			return p;
		},
		[](const volatile auto* p) -> const volatile void*
		{
			return p;
		});

	constexpr auto* to_void_address(auto& o) noexcept
	{
		return to_void_ptr(&o);
	}
}
