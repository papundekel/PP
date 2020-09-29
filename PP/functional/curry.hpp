#pragma once
#include <utility>

namespace PP
{
	constexpr inline auto curry =
		[](auto&& f)
		{
			return
				[f = std::forward<decltype(f)>(f)](auto&& arg)
				{
					return
						[f, arg = std::forward<decltype(arg)>(arg)](auto&&... args) -> decltype(auto)
						{
							return f(arg, std::forward<decltype(args)>(args)...);
						};
				};
		};
}
