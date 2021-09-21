#pragma once
#include "size_t.hpp"
#include "tuple/find_index_state.hpp"
#include "tuple/fold.hpp"
#include "utility/move.hpp"

namespace PP::tuple
{
PP_FUNCTOR(find, auto&& predicate, concepts::tuple auto&& tuple)
{
	return PP_CV_MEMBER(
	    foldl(
	        [predicate_wrap = PP_FW(predicate)](concepts::value auto s,
	                                            auto&& element)
	        {
		        constexpr auto state = PP_GV(s);

		        static_assert(
		            concepts::value<decltype(predicate_wrap(PP_F(element)))>,
		            "tuple::find: the predicate must return a "
		            "concepts::value");

		        if constexpr (state.found ||
		                      PP_GV(predicate_wrap(PP_F(element))))
			        return value<detail::tuple_find_index_state(state.index,
			                                                    true)>;
		        else
			        return value<detail::tuple_find_index_state(state.index + 1,
			                                                    false)>;
	        },
	        value<detail::tuple_find_index_state(0, false)>,
	        PP_F(tuple)),
	    index);
});
}
