#pragma once
#include "decl_type.hpp"
#include "functional/functor.hpp"
#include "type_t.hpp"

namespace PP
{
	template <typename T>
	concept type_wrap = requires
	{
		typename T::type;
	};

	PP_FUNCTOR(get_type, type_wrap auto t)
	{
		return type_v<PP_TYPE_UNSAFE(t)::type>;
	}};

	template <typename T>
	using get_type_t = PP_TYPE_UNSAFE(get_type(type_v<T>));

	#define PP_GET_TYPE(x) ::PP::get_type_t<decltype(x)>
	#define PP_COPY_TYPE(x) (::PP::type_v<PP_GET_TYPE(x)>)

	constexpr inline auto to_type_t = get_type | decl_type_copy;
}
