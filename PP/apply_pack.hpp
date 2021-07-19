#pragma once
#include "functor.hpp"
#include "functor_concept.hpp"
#include "value_sequence.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto apply_pack = functor(
		[]<auto... I>(auto&& packer, auto&& selector, value_sequence<I...>)
			->decltype(auto)
		{
			return unwrap_functor(PP_F(packer))(
				unwrap_functor(PP_F(selector))(value<I>)...);
		});
}
