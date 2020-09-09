#pragma once
#include "type_pack.h"
#include "get_type.h"
#include "apply_pack.h"

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
struct prepend_pack : apply_pack_types<detail::prepend_pack_helper<T>::template help, Pack> {};
