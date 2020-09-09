#pragma once
#include "type_pack.h"
#include "apply_pack.h"
namespace PP
{

}
namespace detail
{
	template <typename... T>
	struct append_pack_helper
	{
		template <typename... U>
		using help = type_t<type_pack<T..., U...>>;

		using type = append_pack_helper<T...>;
	};
}

template <typename X, typename Y>
using append_pack = apply_pack_types<get_type<apply_pack_types<detail::append_pack_helper, X>>::template help, Y>;
