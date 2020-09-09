#pragma once
#include "get_type.h"
#include "apply_pack.h"

namespace PP
{
	namespace detail
	{
		template <typename StartValue, template <typename, typename> typename F>
		struct fold_pack_helper
		{
			template <typename...>
			struct help : type_t<StartValue> {};

			template <typename T, typename... U>
			struct help<T, U...> : help<F<StartValue, T>, U...> {};
		};
	}

	template <typename StartValue, template <typename, typename> typename F, typename Pack>
	struct fold_pack : apply_pack<detail::fold_pack_helper<StartValue, F>::template help, Pack> {};
}
