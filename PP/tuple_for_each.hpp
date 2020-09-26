#pragma once
#include "tuple_apply.hpp"
#include "functional/apply_partially.hpp"

namespace PP
{
	template <bool copy = true>
	constexpr inline auto tuple_for_each = [](auto f)
	{
		return tuple_apply<>(
			[f = std::move(f)]<typename... T>(T&&... t)
			{
				(f(std::forward<T>(t)), ...);
			});
	};
	template <>
	constexpr inline auto tuple_for_each<false> = [](auto& f)
	{
		return tuple_apply<>(
			[&f]<typename... T>(T&&... t)
			{
				(f(std::forward<T>(t)), ...);
			});
	};
}
