#pragma once
#include "../declval.hpp"
#include "../functional/functor.hpp"
#include "../tuple_apply.hpp"
#include "../functional/map_arguments.hpp"

namespace PP
{
	constexpr inline auto is_invocable = map_arguments(tuple_apply,
		[](auto f)
		{
			return [](auto... arg_types)
			{
				return requires
				{
					declval(f)(declval(arg_types)...);
				};
			};
		}, id_forward);

	namespace concepts
	{
		template <typename F, typename... Args>
		concept invocable = is_invocable(type_v<F>, type_tuple_v<Args...>);
	}
}
