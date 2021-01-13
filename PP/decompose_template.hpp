#pragma once
#include "arrow_operator_wrapper.hpp"
#include "functional/compose.hpp"
#include "remove_cvref.hpp"
#include "template_t.hpp"
#include "type_t.hpp"
#include "type_tuple.hpp"

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
	}
	
	constexpr inline auto decompose_template = functor{ overloaded
	{
		[] <template <typename...> typename Template, typename... Types>(PP::type_t<Template<Types...>>)
		{
			return detail::decompose_template_pair{ template_v<Template>, type_tuple_v<Types...> };
		},
		[](auto&&)
		{
			return detail::decompose_template_pair{ template_v<detail::decompose_template_dummy>, type_tuple_v<> };
		}
	}} | remove_cvref;

	constexpr auto operator*(type_wrap auto t) noexcept
	{
		return decompose_template(t);
	}
}
