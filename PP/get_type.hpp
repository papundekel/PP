#pragma once
#include "type_t.hpp"
#include "functional/functor.hpp"

namespace PP
{
	PP_FUNCTOR(get_type, auto t)
	{
		return type_v<PP_TYPE_UNSAFE(t)::type>;
	}};

	template <typename T>
	using get_type_t = PP_TYPE_UNSAFE(get_type(type_v<T>));

	#define PP_GET_TYPE(x) ::PP::get_type_t<decltype(x)>
	#define PP_COPY_TYPE(x) (::PP::type_v<PP_GET_TYPE(x)>)
	
	PP_FUNCTOR(to_type_t, auto t)
	{
		return PP_COPY_TYPE(t);
	}};

	template <typename T>
	concept type_wrap = requires
	{
		typename T::type;
	};
}
