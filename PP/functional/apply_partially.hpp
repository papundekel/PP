#pragma once
#include "../get_value.hpp"
#include "../reference_wrapper.hpp"
#include "../tuple.hpp"
#include "../utility/move.hpp"
#include "apply_pack.hpp"

namespace PP
{
	PP_FUNCTOR(apply_partially, auto&& f, concepts::value auto i, auto&& arg)
	{
		return functor{ [f = PP_FORWARD(f), arg = PP_FORWARD(arg)]
			(auto&&... other_args) -> decltype(auto)
			{
				return apply_pack(f,
					[&arg, args = forward_as_tuple(PP_FORWARD(other_args)...)]
					(concepts::value auto current_i) -> decltype(auto)
					{
						constexpr auto CI = PP_COPY_VALUE(current_i);
						constexpr auto  I = PP_COPY_VALUE(i);

						if constexpr (CI == I)
							return unref(arg);
						else if constexpr (CI < I)
							return move(args)[current_i];
						else
							return move(args)[current_i - value_1];
					}, make_value_sequence(PP_SIZEOF___(other_args) + value_1));
			}};
	}};

	template <typename F>
	constexpr auto functor<F>::operator()(partial_tag_t, auto i, auto&& arg) const& noexcept
	{
		return apply_partially(this->f, i, PP_FORWARD(arg));
	}
	template <typename F>
	constexpr auto functor<F>::operator()(partial_tag_t, auto i, auto&& arg) const&& noexcept
	{
		return apply_partially(move(this->f), i, PP_FORWARD(arg));
	}

	constexpr auto operator*(concepts::functor auto&& f, auto&& arg) noexcept
	{
		return apply_partially(PP_FORWARD(f).f, value_0, PP_FORWARD(arg));
	}
}
