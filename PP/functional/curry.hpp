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

	template <typename F>
	constexpr auto operator~(const functor<F>& f) noexcept
	{
		return curry(f.f);
	}
	template <typename F>
	constexpr auto operator~(const functor<F>&& f) noexcept
	{
		return curry(std::move(f).f);
	}
}
