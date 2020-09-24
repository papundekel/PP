#pragma once
#include <utility>

namespace PP
{
	template <bool copy_f = true, bool copy_args = true>
	constexpr inline auto apply_partially = [](auto f, auto... args)
	{
		return
			[f = std::move(f), ...args = std::move(args)]<typename... OtherArgs>(OtherArgs&&... other_args) -> decltype(auto)
			{
				return f(args..., std::forward<OtherArgs>(other_args)...);
			};
	};
	template <>
	constexpr inline auto apply_partially<false, true> = [](auto& f, auto... args)
	{
		return
			[&f, ...args = std::move(args)]<typename... OtherArgs>(OtherArgs&&... other_args) -> decltype(auto)
			{
				return f(args..., std::forward<OtherArgs>(other_args)...);
			};
	};
	template <>
	constexpr inline auto apply_partially<true, false> = [](auto f, auto&... args)
	{
		return
			[f = std::move(f), &args...]<typename... OtherArgs>(OtherArgs&&... other_args) -> decltype(auto)
			{
				return f(args..., std::forward<OtherArgs>(other_args)...);
			};
	};
	template <>
	constexpr inline auto apply_partially<false, false> = [](auto& f, auto&... args)
	{
		return
			[&f, &args...]<typename... OtherArgs>(OtherArgs&&... other_args) -> decltype(auto)
			{
				return f(args..., std::forward<OtherArgs>(other_args)...);
			};
	};
}
