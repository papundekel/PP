#pragma once
#include "../../functional/functor.hpp"
#include "../../get_type.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		T templated_return_dummy_function(type_t<T>);
	}

	PP_FUNCTOR(is_returnable, concepts::type auto t)
	{
		return requires
		{
			detail::templated_return_dummy_function(to_type_t(t));
		};
	});
}
