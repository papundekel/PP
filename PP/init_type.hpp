#pragma once
#include "declval.hpp"
#include "functor.hpp"
#include "get_type.hpp"
#include "type_t.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_FUNCTOR(init_type, concepts::type auto&& t)
{
	return PP_DT(declval(PP_F(t))());
});
}
