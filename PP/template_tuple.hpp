#pragma once
#include "template_t.hpp"
#include "get_value.hpp"
#include "tuple_recursive.hpp"
#include "tuple_head_no_get.hpp"

namespace PP
{
	template <template <typename...> typename...>
	struct template_tuple {};
	template <template <typename...> typename T, template <typename...> typename... Templates>
	struct template_tuple<T, Templates...>
	{
		constexpr auto head() const noexcept
		{
			return template_v<T>;
		}
		constexpr auto head_element() const noexcept
		{
			return type_v<template_t<T>>;
		}
		constexpr auto pred() const noexcept
		{
			return template_tuple<Templates...>{};
		}
		constexpr auto operator[](value_wrap auto i) const noexcept
		{
			return tuple_recursive(tuple_head_no_get, i, *this);
		}
	};

	template <template <typename...> typename... Templates>
	constexpr inline template_tuple<Templates...> template_tuple_v = {};

	template <template <typename...> typename... Templates>
	constexpr auto tuple_count_implementation(template_tuple<Templates...> t) noexcept
	{
		return value_v<sizeof...(Templates)>;
	};
}
