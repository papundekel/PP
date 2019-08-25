#pragma once
#include "value_t.hpp"
template <template <auto...> typename T>
struct is_template_nontype
{
private:
	template <typename U>
	struct x : value_t<false> {};
	template <auto... U>
	struct x<T<U...>> : value_t<true> {};
public:
	template <typename U>
	using type = value_t<x<U>::v>;
};