#pragma once
#include <utility>

#include "decompose_template.hpp"
#include "get_type.hpp"

namespace PP::concepts
{
	template <typename T>
	concept std_pair = PP::type<T>->Template == template_v<std::pair>;
}

namespace std
{
	constexpr decltype(auto) get(PP::concepts::value auto i, PP::concepts::std_pair auto&& p)
	{
		return std::get<(std::size_t)-PP_DECLTYPE(i)>(PP_FORWARD(p));
	}
	constexpr std::size_t size_implementation(PP::concepts::type auto t)
	requires PP::concepts::std_pair<PP_GET_TYPE(t)>
	{
		return 2;
	}
}
