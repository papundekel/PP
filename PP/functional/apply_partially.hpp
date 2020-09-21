#pragma once
#include <utility>

namespace PP
{
	template <typename F, typename... Args>
	constexpr auto apply_partially(F&& f, Args&&... args) noexcept
	{
		return
			[&f, ...args = std::forward<Args>(args)]<typename... OtherArgs>(OtherArgs&&... other_args)
			{
				return std::forward<F>(f)(args..., std::forward<OtherArgs>(other_args)...);
			};
	}
	template <typename F, typename... Args>
	constexpr auto apply_partially_no_copy(F&& f, Args&&... args) noexcept
	{
		return
			[&f, &args...]<typename... OtherArgs>(OtherArgs&&... other_args)
			{
				return std::forward<F>(f)(std::forward<Args>(args)..., std::forward<OtherArgs>(other_args)...);
			};
	}
}
