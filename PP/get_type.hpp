#pragma once
#include "decl_type.hpp"
#include "functional/compose.hpp"
#include "functional/functor.hpp"
#include "type_t.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept type = requires
		{
			typename T::type;
		};
	}
	
	PP_FUNCTOR(get_type, concepts::type auto t)
	{
		return type<PP_TYPE_UNSAFE(t)::type>;
	});

	template <typename T>
	using get_type_t = PP_TYPE_UNSAFE(get_type(type<T>));

	constexpr auto ffffff(auto x)
	{
		return x;
	}

	#define PP_GET_TYPE(x) ::PP::get_type_t<decltype(ffffff(x))>
	#define PP_COPY_TYPE(x) (::PP::type<PP_GET_TYPE(x)>)

	constexpr inline auto to_type_t = get_type | decl_type_copy;
}
