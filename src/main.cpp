#include "output.hpp"
#include "type_join.hpp"
#include "array.hpp"
#include "accumulate.hpp"
#include "logger.hpp"
#include "make_reference_rvalue.hpp"
#include "number.hpp"

template <typename... T>
struct tuple {};

template <typename T, typename... U>
struct tuple<T, U...> : tuple<U...>
{
	using First = T;
	using Rest = tuple<U...>;

	First first;

	template <typename V, typename... W>
	tuple(V&& v, W&&... w)
		: first(forward<T>(v))
		, tuple<U...>(forward<W>(w)...)
	{}
};

template <typename... T>
tuple(T...) -> tuple<T...>;

template <typename T>
using tuple_first = typename T::First;

template <typename T>
using tuple_rest = typename T::Rest;

template <size_t N, typename T>
constexpr auto& ggg(T& t)
{
	if constexpr (N != 0)
		return ggg<N - 1>(reinterpret_cast<tuple_rest<T>&>(t));
	else
		return t.first;
}

int main()
{
	tuple<int, double, float> a = { 1, 2.0, 5.f };
	print(ggg<0>(a));
	print(ggg<1>(a));
	print(ggg<2>(a));
	return 0;
}