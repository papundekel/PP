#pragma once
#include "string.hpp"
#include "list.hpp"

template <typename unsigned_t, typename container_t = list<unsigned_t>>
container_t divisors(unsigned_t input, bool all = false)
{
	static_assert(std::is_unsigned_v<unsigned_t>);
	container_t container;
	if (all)
	{
		container.push_back(1);
		container.push_back(input);
	}
	auto square_root = math::trunc(sqrt(input)) + 1;
	for (unsigned_t i = 2; i < square_root; ++i)
		if (input % i == 0)
		{
			if (i != input / i)
				container.insert(container.begin() + container.size_t() / 2, input / i);
			container.insert(container.begin() + container.size_t() / 2, i);
		}
	return container;
}

bool isPalindrome(const string& input);

template <typename string_convertible_t>
bool isPalindrome(const string_convertible_t& input)
{
	static_assert(std::is_convertible_v<string_convertible_t, string>);

	return isPalindrome(string(input));
}

template <typename unsigned_t>
bool is_prime(unsigned_t input)
{
	static_assert(std::is_unsigned_v<unsigned_t>);

	if (input % 2 == 0)
		return false;
	if (input % 3 == 0)
		return false;
	if (input == 1)
		return false;
	if (input < 4)
		return true;
	if (input < 9)
		return true;
	else
	{
		unsigned_t temp = math::trunc<unsigned_t>(sqrt(input));
		unsigned_t f = 5;

		while (f <= temp)
		{
			if (input % f == 0)
			{
				return false;
			}
			if (input % (f + 2) == 0)
			{
				return false;
			}
			f = f + 6;
		}

		return true;
	}
}