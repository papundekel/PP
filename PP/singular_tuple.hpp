#pragma once
#include "utility/forward.hpp"
#include "get_type.hpp"

namespace PP
{
	template <typename T>
	class singular_tuple
	{
		T obj;

	public:
		constexpr singular_tuple(auto&& obj)
			: obj(PP_FORWARD(obj))
		{}
	};
	template <typename T>
	singular_tuple(T)->singular_tuple<T>;

	constexpr auto make_singular_tuple(auto&& x)
	{
		return singular_tuple<PP_GET_TYPE(~PP_DECLTYPE(x))>(PP_FORWARD(x));
	}
	constexpr auto forward_as_singular_tuple(auto&& x) noexcept
	{
		return singular_tuple<decltype(x)>(PP_FORWARD(x));
	}
}
