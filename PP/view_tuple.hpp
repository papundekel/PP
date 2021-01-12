#pragma once
#include <tuple>
#include <type_traits>
#include <limits>
#include "view.hpp"
#include "value_t.hpp"

namespace PP
{
	template <iterator Iterator, std::size_t Count = std::numeric_limits<std::size_t>::max()>
	class view_tuple
	{
		Iterator begin;

	public:
		explicit constexpr view_tuple(Iterator begin, PP::value_t<Count> = {}) noexcept
			: begin(begin)
		{}
		explicit constexpr view_tuple(view auto v, PP::value_t<Count> = {}) noexcept
			: begin(begin(v))
		{}

		template <std::size_t I, iterator It, std::size_t C>
		friend constexpr decltype(auto) get(value_t<I>, view_tuple<It, C> v_tuple) noexcept
		{
			return v_tuple.begin[I];
		};
	};
}

namespace std
{
	template <typename Iterator, std::size_t Count>
	struct tuple_size<PP::view_tuple<Iterator, Count>> : public integral_constant<size_t, Count> {};
	template <std::size_t I, typename Iterator, std::size_t Count>
	struct tuple_element<I, PP::view_tuple<Iterator, Count>> : public type_identity<PP::iterator_base_t<Iterator>> {};
}
