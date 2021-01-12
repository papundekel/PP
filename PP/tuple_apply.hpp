#pragma once
#include <utility>

#include "forward.hpp"
#include "functional/functor.hpp"
#include "tuple_get.hpp"
#include "tuple_index_sequence_for.hpp"
#include "tuple_like.hpp"
#include "tuple_size.hpp"
#include "value_t.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_apply, auto&& f, tuple_like auto&& tuple) -> decltype(auto)
	{
		return
			[&f, &tuple]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto)
			{
				return PP_FORWARD(f)(get(value_v<I>, PP_FORWARD(tuple))...);
			}(tuple_index_sequence_for(tuple));
	}};

	template <typename F>
	constexpr decltype(auto) functor<F>::operator[](auto&& tuple) const&
	{
		return tuple_apply(f, PP_FORWARD(tuple));
	}
	template <typename F>
	constexpr decltype(auto) functor<F>::operator[](auto&& tuple) const&&
	{
		return tuple_apply(std::move(f), PP_FORWARD(tuple));
	}
}
