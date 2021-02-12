#pragma once
#include "functional/functor.hpp"
#include "get_type.hpp"
#include "type_t.hpp"

namespace PP
{
	PP_FUNCTOR(construct_pack, concepts::type auto t, auto&&... args) -> decltype(auto)
	{
		return PP_GET_TYPE(t)(PP_FORWARD(args)...);
	}};

	template <typename T>
	constexpr decltype(auto) type_t<T>::operator()(auto&&... args) const
	{
		return construct_pack(*this, PP_FORWARD(args)...);
	}
}
