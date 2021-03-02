#pragma once

namespace PP
{
	constexpr void* to_void_ptr(auto& o) noexcept
	{
		return &o;
	}
	constexpr const void* to_void_ptr(const auto& o) noexcept
	{
		return &o;
	}
}
