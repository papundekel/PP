#include "output.hpp"
#include "type_join.hpp"
#include "array.hpp"
#include "accumulate.hpp"
#include "logger.hpp"
#include "make_reference_rvalue.hpp"
#include "number.hpp"

template <typename... T>
struct types2
{
	
};

template <typename T, typename... U>
struct types2<T>
{
	using t = T;
};

template <typename T>
constexpr auto size2 = sizeof

template <auto F>
struct wrapper
{
	constexpr auto operator()
};

int main()
{
	int a = 5;

	//A{a};
	print(constructible<A, int&>);

	return 0;
}