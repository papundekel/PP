#pragma once
#include "tuple.hpp"
#include "view_zip_with.hpp"

namespace PP
{
	PP_FUNCTOR(zip_with_pack, auto&& f, concepts::view auto&&... views)
	{
		return zip_with(PP_FORWARD(f), forward_as_tuple(PP_FORWARD(views)...));
	}};
}
