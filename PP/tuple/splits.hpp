#pragma once
#include "../containers/tuple.hpp"
#include "../forward_wrap.hpp"
#include "../get_value.hpp"
#include "../type_t.hpp"
#include "empty.hpp"
#include "fold.hpp"
#include "make.hpp"
#include "prepend.hpp"
#include "zip_indices.hpp"

namespace PP::tuple
{
PP_FUNCTOR(splits, auto&& pp, concepts::tuple auto&& t)
{
	return foldr(
	    [p = PP_FW(pp)](auto&& element, auto splits)
	    {
		    if constexpr (PP_GV(p(PP_F(element))))
			    return !prepend(tuple_empty{}, move(splits));
		    else
			    return *functor(
			               [element_wrap = PP_FW(
			                    element)](concepts::value auto i, auto split)
			               {
				               if constexpr (PP_GV(i) == 0)
					               return prepend(element_wrap--, move(split));
				               else
					               return move(split);
			               }) +
			           zip_indices(move(splits));
	    },
	    make_tuple(tuple_empty{}),
	    PP_F(t));
});
}
