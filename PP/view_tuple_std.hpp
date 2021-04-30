#pragma once
#include <tuple>

#include "view_tuple.hpp"

namespace std
{
	template <typename Iterator, size_t Count>
	struct tuple_size<PP::concepts::view_tuple<Iterator, Count>>
		: public integral_constant<size_t, Count>
	{};
	template <size_t I, typename Iterator, size_t Count>
	struct tuple_element<I, PP::concepts::view_tuple<Iterator, Count>>
		: public type_identity<PP::iterator_base_t<Iterator>>
	{};
}
