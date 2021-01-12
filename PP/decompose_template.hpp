#pragma once
#include "template_t.hpp"
#include "type_tuple.hpp"
#include "type_t.hpp"
#include "remove_cvref.hpp"
#include "functional/compose.hpp"
#include "arrow_operator_wrapper.hpp"

namespace PP
{
	template <typename T>
	constexpr auto type_t<T>::operator->() const noexcept
	{
		return arrow_operator_wrapper(**this);
	}

	namespace detail
	{
		template <template <typename...> typename T, typename... Types>
		struct decompose_template_pair
		{
			template_t<T> Template;
			type_tuple<Types...> types;
		};

		template <typename T>
		struct decompose_template_dummy {};

		constexpr inline functor decompose_template_helper
		{
			overloaded
			{
				[]<template <typename...> typename Template, typename... Types>(PP::type_t<Template<Types...>>)
				{
					return decompose_template_pair{ template_v<Template>, type_tuple_v<Types...> };
				},
				[](auto&&)
				{
					return decompose_template_pair{ template_v<decompose_template_dummy>, type_tuple_v<> };
				}
			}
		};
	}
	
	constexpr inline auto decompose_template = detail::decompose_template_helper | remove_cvref;

	constexpr auto operator*(type_t<auto> t) noexcept
	{
		return decompose_template(t);
	}
}
