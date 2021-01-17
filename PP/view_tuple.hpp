#pragma once
#include "get_value.hpp"
#include "get_type.hpp"
#include "remove_cvref.hpp"
#include "utility/move.hpp"
#include "view.hpp"

namespace PP
{
	template <concepts::iterator Iterator>
	class view_tuple
	{
		Iterator begin;

	public:
		explicit constexpr view_tuple(Iterator begin) noexcept
			: begin(move(begin))
		{}

		constexpr decltype(auto) operator[](value_wrap auto i) const noexcept
		{
			return begin[*i];
		};
		constexpr auto element(value_wrap auto i) const noexcept
		{
			return PP_DECLTYPE(operator[](i));
		}
		constexpr auto tuple_count() const noexcept
		{
			return value_v<std::size_t(0) - 1>;
		}
	};
	constexpr auto make_view_tuple(concepts::view auto&& v) noexcept
	{
		return view_tuple(view_begin(PP_FORWARD(v)));
	}
}
