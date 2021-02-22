#pragma once
#include <tuple>

#include "zip_view.hpp"
#include "get_std.hpp"

namespace std
{
	template <typename... Iterators>
	struct tuple_size<PP::zip_iterator<Iterators...>> : public tuple_size<tuple<Iterators...>> {};
	template <std::size_t I, typename... Iterators>
	struct tuple_element<I, PP::zip_iterator<Iterators...>> : public tuple_element<I, tuple<Iterators...>> {};
}
