#pragma once
#include "get_type.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_FUNCTOR(reinterpret__cast, concepts::type auto t, auto&& value)
    -> decltype(auto)
{
	return reinterpret_cast<PP_GT(t)>(PP_F(value));
});
}
