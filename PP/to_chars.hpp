#pragma once
#include <cstddef>
#include <algorithm>

namespace PP
{
	constexpr std::size_t to_chars(char* begin, char* end, std::size_t value) noexcept
	{
		if (value == 0)
		{
			if (begin != end)
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

		std::move(i, end, begin);

		return end - i;
	}
}
