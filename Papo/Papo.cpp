#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include "any_of.hpp"
#include "transform_view.hpp"
#include "zip_with.hpp"
#include "copy.hpp"
#include "move.hpp"
#include "simple_vector.hpp"

struct X
{
	X() = default;
	X(const X&) = default;
	X(X&&) = default;
	X& operator=(X&&) noexcept
	{
		std::cout << "moved\n";
		return *this;
	}
};

int main()
{
	Papo::simple_vector<X> v;
	v.push_back(X{});
	v.push_back(X{});
	v.push_back(X{});
	v.push_back(X{});

	std::array<X, 4> a;

	Papo::move(v, a);

	std::cout.flush();
	return 0;
}
