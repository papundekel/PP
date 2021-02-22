#pragma once
#include <memory>

#include "functional/functor.hpp"
#include "get_type.hpp"

namespace PP
{
	PP_FUNCTOR(construct_at_pack, auto* p, auto&&... args) -> decltype(auto)
	{
		return std::construct_at(p, PP_FORWARD(args)...);
	});
}
