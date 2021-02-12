#pragma once
#include "simple_view.hpp"
#include "unbounded.hpp"
#include "view_move.hpp"

namespace PP
{
	constexpr size_t to_chars(concepts::view auto&& v, auto value) noexcept
	{
		auto [begin, end] = PP::view_begin_end(PP_FORWARD(v));

		if (value == 0)
		{
			if (begin == end)
			{
				*begin = '0';
				return 1;
			}
			else
				return 0;
		}

		auto i = end;

		while (i != begin && value != 0)
		{
			auto digit = value % 10;
			value /= 10;
			*(--i) = char('0' + digit);
		}

		view_move(begin ^ unbounded, simple_view(i, end));

		return end - i;
	}
}
