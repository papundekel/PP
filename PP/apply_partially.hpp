#pragma once
#include "apply_pack.hpp"
#include "apply_partially_first.hpp"
#include "containers/tuple.hpp"
#include "functor.hpp"
#include "get_value.hpp"
#include "utility/move.hpp"

namespace PP
{
PP_FUNCTOR(apply_partially, auto&& f, concepts::value auto i, auto&& arg)
{
	return functor(
	    [f = PP_F(f), arg = PP_F(arg)](auto&&... other_args) -> decltype(auto)
	    {
		    return apply_pack(
		        unwrap_forward(f),
		        [&arg, args = tuple::forward(PP_F(other_args)...)](
		            concepts::value auto current_i) -> decltype(auto)
		        {
			        constexpr auto CI = PP_CV(current_i);
			        constexpr auto I = PP_CV(i);

			        if constexpr (CI == I)
				        return unwrap_forward(arg);
			        else if constexpr (CI < I)
				        return move(args)[current_i];
			        else
				        return move(args)[current_i - value_1];
		        },
		        value_sequence_make(PP_SIZEOF___(other_args) + value_1));
	    });
});
}

template <typename F>
constexpr auto PP::functor<F>::operator()(partial_tag_t,
                                          auto i,
                                          auto&& arg) const& noexcept
{
	return apply_partially(unwrap_functor(*this), i, PP_F(arg));
}
template <typename F>
constexpr auto PP::functor<F>::operator()(partial_tag_t,
                                          auto i,
                                          auto&& arg) const&& noexcept
{
	return apply_partially(unwrap_functor(move(*this)), i, PP_F(arg));
}
