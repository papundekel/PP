#pragma once
#include "type_pack.hpp"
#include "get_type.hpp"
#include "apply_pack.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		struct prepend_pack_helper : type_t<prepend_pack_helper<T>>
		{
			template <typename... U>
			struct help : type_t<type_pack<T, U...>> {};
		};
	}

	template <typename T, typename Pack>
	using prepend_pack = apply_pack_types<detail::prepend_pack_helper<T>::template help, Pack>;
}
