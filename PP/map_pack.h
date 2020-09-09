#pragma once
#include <array>
#include "get_value.h"
#include "apply_pack.h"
#include "get_type.h"
#include "value_t.h"

namespace detail
{
	template <template <typename> typename Map, typename ElementType>
	struct map_pack_helper
	{
		template <typename... T>
		struct mapper
		{
			static constexpr std::array<ElementType, sizeof...(T)> value = { get_value<Map<T>>()... };
		};
	};
	template <template <typename> typename Map>
	struct map_pack_types_helper
	{
		template <typename... T>
		using mapper = type_t<type_pack<get_type<Map<T>>...>>;
	};
}

template <template <typename> typename Map, typename Pack, typename ElementType>
using map_pack = apply_pack<detail::map_pack_helper<Map, ElementType>::template mapper, Pack>;

template <template <typename> typename Map, typename Pack>
using map_pack_types = apply_pack_types<detail::map_pack_types_helper<Map>::template mapper, Pack>;
