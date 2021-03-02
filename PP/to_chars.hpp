#pragma once
#include "simple_view.hpp"
#include "unbounded.hpp"
#include "view_move.hpp"

namespace PP
{
	constexpr auto to_chars(concepts::view auto&& v, auto value) noexcept
	{
		auto [begin, end] = PP::view_begin_end(PP_FORWARD(v));

		if (begin == end)
			return begin;

		if (value == 0 && begin != end)
		{
			*begin = '0';
			return ++begin;
		}

		auto i = end;

		bool was_negative = false;

		constexpr bool signed_type = decltype(value)(-1) < decltype(value)(0);

		if constexpr (signed_type)
		{
			if (value < 0)
			{
				was_negative = true;
				value = -value;
			}
		}

		while (i != begin && value != 0)
		{
			auto digit = value % 10;
			value /= 10;
			--i;
			*i = char('0' + digit);
		}

		if constexpr (signed_type)
		{
			if (was_negative && i != begin)
			{
				--i;
				*i = '-';
			}
		}

		return view_move(begin ^ unbounded, i ^ end)[value_0];
	}
}
