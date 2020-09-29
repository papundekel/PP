#pragma once
#include <utility>

namespace PP
{
	template <bool copy_f = true, bool copy_maps = true>
	constexpr inline auto map_arguments =
		[](auto& f, auto&... maps)
		{
			return [&f, &maps...](auto&&... args) -> decltype(auto)
			{
				return f(maps(std::forward<decltype(args)>(args))...);
			};
		};
	template <>
	constexpr inline auto map_arguments<false, true> =
		[](auto& f, auto&&... maps)
		{
			return [&f, ...maps = std::forward<decltype(maps)>(maps)](auto&&... args) -> decltype(auto)
			{
				return map_arguments<false, false>(f, maps...)(std::forward<decltype(args)>(args)...);
			};
		};
	template <>
	constexpr inline auto map_arguments<true, false> =
		[](auto&& f, auto&... maps)
		{
			return [f = std::forward<decltype(f)>(f), &maps...](auto&&... args) -> decltype(auto)
			{
				return map_arguments<false, false>(f, maps...)(std::forward<decltype(args)>(args)...);
			};
		};
	template <>
	constexpr inline auto map_arguments<true, true> =
		[](auto&& f, auto&&... maps)
		{
			return [f = std::forward<decltype(f)>(f), ...maps = std::forward<decltype(maps)>(maps)](auto&&... args) -> decltype(auto)
			{
				return map_arguments<false, false>(f, maps...)(std::forward<decltype(args)>(args)...);
			};
		};
}
