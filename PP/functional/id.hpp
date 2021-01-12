#pragma once
#include "functor.hpp"
#include "../type_t.hpp"

namespace PP
{
	constexpr inline functor id
	{
		[]<typename T>(type_t<T>, type_t<T>::type t) -> decltype(auto)
		{
			return static_cast<T>(t);
		}
	};

	constexpr inline functor id_weak
	{
		[](auto&& t) -> decltype(auto)
		{
			return PP_FORWARD(t);
		}
	};
}
