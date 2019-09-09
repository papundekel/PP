#pragma once
#include "val.hpp"
template <template <auto...> typename T>
struct is_template_nontype
{
private:
	template <typename U>
	struct x : val<false> {};
	template <auto... U>
	struct x<T<U...>> : val<true> {};
public:
	template <typename U>
	using type = val<x<U>::v>;
};