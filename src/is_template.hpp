#pragma once
#include "value_t.hpp"
template <template <typename...> typename T>
struct is_template
{
private:
	template <typename U>
	struct x : value_t<false> {};
	template <typename... U>
	struct x<T<U...>> : value_t<true> {};
public:
	template <typename U>
	using type = value_t<x<U>::v>;
};