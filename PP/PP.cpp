#include <iostream>

#include "remove_cvref.hpp"
#include "pointer_stack.hpp"
#include "tuple_size.hpp"
#include "tuple.hpp"
#include "array.hpp"

#include "tuple_fold.hpp"

#include "tuple_zip_with.hpp"

struct S
{
	S() = default;
	constexpr S(const S&)
	{
		std::cout << "copied\n";
	}
	constexpr S(S&&)
	{
		std::cout << "moved\n";
	}
};

int main()
{
	char c = 2;
	int i = 7;

	auto t = PP::forward_as_tuple(c, i);

	auto u = PP::make_tuple(1, nullptr);

	long long xxx = 0;

	auto x = PP::tuple_zip(PP::forward_as_tuple(t, u));

	std::cout.flush();
	return 0;
}
