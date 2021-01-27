#pragma once
#include "functional/apply_pack.hpp"
#include "functional/functor.hpp"
#include "reference_wrapper.hpp"
#include "tuple_count.hpp"
#include "tuple_get.hpp"
#include "tuple_value_sequence_for.hpp"
#include "tuple_like.hpp"
#include "utility/forward.hpp"
#include "value_t.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_apply, auto&& f, concepts::tuple auto&& t) -> decltype(auto)
	{
		return apply_pack(PP_FORWARD(f), tuple_get(partial_tag, value_1, ref(PP_FORWARD(t))), tuple_value_sequence_for(PP_FORWARD(t)));
	}};

	template <typename F>
	constexpr decltype(auto) functor<F>::operator[](auto&& t) const&
	{
		return tuple_apply(f, PP_FORWARD(t));
	}
	template <typename F>
	constexpr decltype(auto) functor<F>::operator[](auto&& t) const&&
	{
		return tuple_apply(std::move(f), PP_FORWARD(t));
	}
}
