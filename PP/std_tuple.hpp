#pragma once
#include <tuple>

#include "decompose_template.hpp"
#include "remove_cvref.hpp"
#include "type_t.hpp"

namespace PP::concepts
{
	template <typename T>
	concept std_tuple = PP::type<T>->Template == template_v<std::tuple>;
}

namespace std
{
	constexpr decltype(auto) get(PP::concepts::value auto i, PP::concepts::std_tuple auto&& t) noexcept
	{
		return std::get<(size_t)*PP_COPY_VALUE(i)>(PP_FORWARD(t));
	}
	constexpr decltype(auto) size_implementation(auto t) noexcept
	requires PP::concepts::std_tuple<PP_GET_TYPE(t)>
	{
		return std::tuple_size_v<~PP_GET_TYPE(t)>;
	}
}
