#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(curry, auto&& f)
	{
		return functor{
			[f_copy = PP_FORWARD(f)] (auto&& arg)
			{
				return functor{
					[f_copy, arg = PP_FORWARD(arg)] (auto&&... args) -> decltype(auto)
					{
						return f_copy(arg, PP_FORWARD(args)...);
					}};
			}};
	}};

	constexpr auto operator~(is_functor auto&& f) noexcept
	{
		return curry(PP_FORWARD(f).f);
	}
}
