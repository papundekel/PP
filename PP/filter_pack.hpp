#pragma once
#include "type_pack.hpp"
#include "get_value_type.hpp"
#include "prepend_pack.hpp"

namespace PP
{
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
	using filter_pack = apply_pack_types<filter_helper<Predicate>::template help, Pack>;
}
