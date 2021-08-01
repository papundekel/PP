#pragma once
#include "get_value.hpp"
#include "template_t.hpp"
#include "tuple/head_no_get.hpp"
#include "tuple/recursive.hpp"

namespace PP
{
template <template <typename...> typename...>
struct template_tuple_t
{};
template <template <typename...> typename T,
          template <typename...>
          typename... Templates>
struct template_tuple_t<T, Templates...>
{
	constexpr auto head() const noexcept
	{
		return Template<T>;
	}
	constexpr auto head_element() const noexcept
	{
		return type<template_t<T>>;
	}
	constexpr auto pred() const noexcept
	{
		return template_tuple_t<Templates...>{};
	}
	constexpr auto operator[](concepts::value auto i) const noexcept
	{
		return tuple::recursive(tuple::head_no_get, i, *this);
	}
};

template <template <typename...> typename... Templates>
constexpr inline template_tuple_t<Templates...> template_tuple = {};

template <template <typename...> typename... Templates>
constexpr auto tuple_count_impl(template_tuple_t<Templates...>) noexcept
{
	return value<sizeof...(Templates)>;
}
}
