#pragma once
#include "../apply_partially_first.hpp"
#include "../constant.hpp"
#include "../construct_pack.hpp"
#include "empty.hpp"
#include "tuple/fold.hpp"
#include "tuple/make.hpp"
#include "tuple/prepend.hpp"

namespace PP::tuple
{
PP_FUNCTOR(oncat, concepts::tuple auto&& l, concepts::tuple auto&& r)
{
	return foldr(prepend, forward(PP_F(r)), PP_F(l));
});

PP_FUNCTOR(concats, concepts::tuple auto&& tuples)
{
	return foldl(concat, tuple_empty{}, PP_F(tuples));
});

constexpr inline auto concats_pack = concats | forward_as_tuple;
}
