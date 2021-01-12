#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(apply_partially, auto&& f, auto&&... args)
	{
		return functor{
			[f = PP_FORWARD(f), ...args = PP_FORWARD(args)] (auto&&... other_args) -> decltype(auto)
			{
				return f(args..., PP_FORWARD(other_args)...);
			}};
	}};

	template <typename T>
	constexpr auto functor<T>::operator()(partial_tag_t, auto&&... args) const&
	{
		return apply_partially(f, PP_FORWARD(args)...);
	}
	template <typename T>
	constexpr auto functor<T>::operator()(partial_tag_t, auto&&... args) const&&
	{
		return apply_partially(std::move(f), PP_FORWARD(args)...);
	}
}
