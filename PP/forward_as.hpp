#pragma once
#include "apply_template.hpp"

namespace PP
{
	PP_FUNCTOR(forward_as, auto Template, auto&&... args)
	{
		return PP_GT(apply_template_pack(Template, PP_DECLTYPE(args)...)){
			PP_F(args)...};
	});
}
