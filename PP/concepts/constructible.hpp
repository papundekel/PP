#pragma once
#include "../declval.hpp"
#include "../functional/functor.hpp"
#include "../tuple_apply.hpp"
#include "../functional/map_arguments.hpp"

namespace PP
{
	constexpr inline auto is_constructible = map_arguments(tuple_apply,
		[](auto t)
		{
			return [t](auto... as)
			{
				return requires
				{
					declval(t)(declval(as)...);
				};
			};
		}, id_weak);

	namespace concepts
	{
		template <typename T, typename... Args>
		concept constructible = is_constructible(type_v<T>, type_tuple_v<Args...>);
	}
}
