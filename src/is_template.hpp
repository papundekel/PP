#pragma once
#include "val.hpp"
template <template <typename...> typename T>
struct is_template
{
private:
	template <typename U>
	struct x : val<false> {};
	template <typename... U>
	struct x<T<U...>> : val<true> {};
public:
	template <typename U>
	using type = val<x<U>::v>;
};