#pragma once
#include "get_value.hpp"
#include "view.hpp"

namespace PP
{
	template <iterator Iterator>
	class view_tuple
	{
		Iterator begin;

	public:
		explicit constexpr view_tuple(Iterator begin) noexcept
			: begin(begin)
		{}
		explicit constexpr view_tuple(view auto&& v) noexcept
			: begin(begin(PP_FORWARD(v)))
		{}

		template <iterator It>
		friend constexpr decltype(auto) get(value_wrap auto i, view_tuple<It> v_tuple) noexcept
		{
			return v_tuple.begin[*i];
		};
	};
}
