#pragma once
#include <system_error>

struct to_chars_result
{
	char* end;
	std::errc error_code;
};
template <typename it, typename = enable_if<is_same<char, typename it::base_type>>>
to_chars_result to_chars(it begin, it end, int value)
{
	if (begin != end)
	{
		int divisor = math::pow(10u, math::trunc(log10(value)));

		if (value < 0)
		{
			value = -value;
			*begin++ = '-';
		}

		while (value != 0)
		{
			if (begin == end)
				return { begin, std::errc::value_too_large };
			*begin++ = '0' + value / divisor;
			value %= divisor;
			divisor /= 10;
		}
	}

	return { begin, std::errc() };
}