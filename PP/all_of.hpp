#pragma once
#include <utility>
#include "view.hpp"
#include "functional/id.hpp"

namespace PP
{
	PP_FUNCTOR(all_of, concepts::view auto&& v, auto&& p = id_forward)
	{
		for (auto&& e : PP_FORWARD(v))
			if (!PP_FORWARD(p)(e))
				return false;
		return true;
	}};
}
