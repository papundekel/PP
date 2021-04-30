#pragma once
#include "functional/apply_pack.hpp"
#include "functional/functor.hpp"
#include "tuple_count.hpp"
#include "tuple_get.hpp"
#include "tuple_like.hpp"
#include "tuple_value_sequence_for.hpp"
#include "utility/forward.hpp"
#include "value_t.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_apply, auto&& f, concepts::tuple auto&& t)
		-> decltype(auto)
	{
		return apply_pack(unwrap_functor(PP_FORWARD(f)),
						  tuple_get(partial_tag, value_1, PP_FORWARD_WRAP(t)),
						  tuple_value_sequence_for(PP_FORWARD(t)));
	});

	template <typename F>
	constexpr decltype(auto) functor<F>::operator[](auto&& t) const&
	{
		return tuple_apply(*this, PP_FORWARD(t));
	}
	template <typename F>
	constexpr decltype(auto) functor<F>::operator[](auto&& t) const&&
	{
		return tuple_apply(move(*this), PP_FORWARD(t));
	}
}
