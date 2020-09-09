#pragma once
#include "type_pack.h"
#include "get_value_type.h"
#include "prepend_pack.h"

template <template <typename> typename Predicate>
struct filter_helper
{
	template <typename...>
	struct help : type_t<type_pack<>>
	{};
	template <typename Head, typename... Tail>
	struct help<Head, Tail...>
	{
		static constexpr auto value_f() noexcept
		{
			using FilteredTail = help<Tail...>;

			if constexpr (get_value<Predicate<Head>>())
				return prepend_pack<Head, FilteredTail>{};
			else
				return FilteredTail{};
		}
		
		using type = get_type<get_value_type<help>>;
	};
};

template <template <typename> typename Predicate, typename Pack>
struct filter_pack : apply_pack_types<filter_helper<Predicate>::template help, Pack> {};
