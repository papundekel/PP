#pragma once
#include "../../functor.hpp"
#include "../../get_type.hpp"
#include "../../templated_dummy.hpp"

namespace PP
{
PP_FUNCTOR(is_pointable, concepts::type auto t)
{
	return requires
	{
		typename detail::templated_dummy<PP_GT(t)*>;
	};
});
}
