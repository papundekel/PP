#pragma once
#include "forward_wrap.hpp"
#include "functor_concept.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept forward_wrap = requires(T t)
		{
			[]<typename U>(const forward_wrap<U>&)
			{
			}(t);
		};

		template <typename T>
		concept wrap = functor<T> || forward_wrap<T>;
	}

	constexpr auto&& unwrap(auto&& f)
	{
		if constexpr (concepts::wrap<decltype(f)>)
		{
			return unwrap_functor(unwrap_forward(PP_F(f)));
		}
		else
			return PP_F(f);
	}
}
