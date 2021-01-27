#pragma once
#include "../declval.hpp"
#include "../functional/apply_partially.hpp"
#include "../get_type.hpp"
#include "../tuple_apply.hpp"

namespace PP
{
	PP_FUNCTOR(is_constructible_pack, concepts::type auto t, concepts::type auto... arg_types)
	{
		return requires
		{
			PP_GET_TYPE(t)(declval(arg_types)...);
		};
	}};

	PP_FUNCTOR(is_constructible, concepts::type auto t, concepts::tuple auto arg_tuple)
	{
		return (is_constructible_pack * t)[arg_tuple];
	}};

	namespace concepts
	{
		template <typename T, typename... Args>
		concept constructible = is_constructible_pack(PP::type<T>, PP::type<Args>...);
	}
}
