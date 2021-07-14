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
		concept functor_or_wrap = functor<T> || forward_wrap<T>;
	}

	constexpr auto&& unwrap_functor_or_wrap(auto&& f)
	{
		if constexpr (concepts::functor_or_wrap<decltype(f)>)
			return unwrap_functor_or_wrap(
				unwrap_forward(unwrap_functor(PP_FORWARD(f))));
		else
			return PP_FORWARD(f);
	}
}
