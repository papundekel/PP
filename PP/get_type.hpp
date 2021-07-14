#pragma once
#include "compose.hpp"
#include "decl_type.hpp"
#include "functor.hpp"
#include "remove_reference_impl.hpp"
#include "type_t.hpp"

namespace PP
{
	template <typename T>
	using get_type_t = remove_reference_impl<T>::type;

	namespace concepts
	{
		template <typename T>
		concept type = requires
		{
			typename remove_reference_impl<T>::type;
		};
	}

	PP_FUNCTOR(get_type, concepts::type auto&& t)
	{
		return type<get_type_t<get_type_t<decltype(t)>>>;
	});

#undef PP_GET_TYPE_HELPER

#define PP_GET_TYPE(x) ::PP::get_type_t<decltype(x)>
#define PP_COPY_TYPE(x) (::PP::type<PP_GET_TYPE(x)>)

	constexpr inline auto to_type_t = get_type | decl_type_copy;
}
