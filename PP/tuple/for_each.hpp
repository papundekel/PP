#pragma once
#include "../apply_partially_first.hpp"
#include "../compose.hpp"
#include "../empty.hpp"
#include "../forward_wrap.hpp"
#include "fold.hpp"

namespace PP::tuple
{
PP_FUNCTOR(for_each_dir,
           concepts::value auto left,
           auto&& ff,
           concepts::tuple auto&& t)
{
	fold(
	    left,
	    [f = PP_FW(ff)](empty, auto&& element)
	    {
		    f(PP_F(element));
		    return empty{};
	    },
	    empty{},
	    PP_F(t));
});

PP_CIA for_each = for_each_dir * value_true;
}
