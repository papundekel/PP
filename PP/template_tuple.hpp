#pragma once
#include <tuple>
#include "template_t.hpp"
#include "value_t.hpp"
#include "type_t.hpp"

namespace PP
{
	template <template <typename...> typename... Templates>
	struct template_tuple {};

	template <template <typename...> typename... Templates>
	constexpr inline template_tuple<Templates...> template_tuple_v = {};

	template <auto I, template <typename...> typename H, template <typename...> typename... T>
	constexpr auto& get(value_t<I>, template_tuple<H, T...>) noexcept
	{
		if constexpr (I == 0)
			return template_v<H>;
		else
			return get(value_v<I - 1>, template_tuple_v<T...>);
	};
	template <template <typename...> typename... T>
	constexpr std::size_t size_implementation(type_t<template_tuple<T...>>) noexcept
	{
		return sizeof...(T);
	};
}

namespace std
{
	template <template <typename...> typename... Templates>
	struct tuple_size<PP::template_tuple<Templates...>> : public tuple_size<std::tuple<PP::template_t<Templates>...>> {};

	template <std::size_t I, template <typename...> typename... Templates>
	struct tuple_element<I, PP::template_tuple<Templates...>> : public tuple_element<I, std::tuple<PP::template_t<Templates>...>> {};
}
