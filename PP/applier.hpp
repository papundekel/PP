#pragma once
#include "apply_partially.hpp"
#include "tuple/apply.hpp"

namespace PP
{
PP_FUNCTOR(applier, auto&& f)
{
	return tuple::apply * PP_F(f);
});
}

constexpr auto operator*(PP::concepts::wrap auto&& f)
{
	return PP::applier(PP_UF(f));
}
