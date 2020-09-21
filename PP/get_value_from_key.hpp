#pragma once
#include <utility>
#include "type_t.hpp"
#include "get_value.hpp"
#include "conditional.hpp"
#include "get_type.hpp"
#include "functional/equal.hpp"
#include "tuple_like.hpp"
namespace PP
{
	namespace detail
	{
		template <auto equality, typename Key, typename Default>
		struct get_value_from_key_helper
		{
			constexpr auto operator()()
			{
				return Default{};
			}
			template <tuple_like F>
			constexpr decltype(auto) operator()(F, auto... rest)
			{
				if constexpr (equality(Key{}, std::get<0>(F{})))
					return std::get<1>(F{});
				else
					return (*this)(rest...);
			}
		};
	}

	template <typename T, typename U>
	using type_pair = std::pair<PP::type_t<T>, PP::type_t<U>>;

	struct key_not_found__error {};

	template <auto equality = equal, typename Key, typename Tuple, typename Default = key_not_found__error>
	constexpr auto get_value_from_key(Key, Tuple&& tuple, Default = {})
	{
		return std::apply(detail::get_value_from_key_helper<equality, Key, Default>{}, std::forward<Tuple>(tuple));
	}
}
