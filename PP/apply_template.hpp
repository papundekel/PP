#pragma once
#include "get_type.hpp"
#include "get_value.hpp"
#include "functional/functor.hpp"
#include "template_t.hpp"
#include "tuple_index_sequence_for.hpp"
#include "tuple_like.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <template <typename...> typename Template, std::size_t... I>
		constexpr auto apply_template_helper(template_t<Template>, auto&& types, std::index_sequence<I...>) noexcept
		{
			return type_v<Template<PP_GET_TYPE(get(PP::value_v<I>, PP_FORWARD(types)))...>>;
		};
	}

	PP_FUNCTOR(apply_template, auto Template, tuple_like auto&& types)
	{
		return detail::apply_template_helper(Template, PP_FORWARD(types), tuple_index_sequence_for(types));
	}};

	constexpr inline auto apply_template_type = get_type | apply_template;
	constexpr inline auto apply_template_value = get_value | apply_template

	template <template <typename...> typename Template>
	constexpr auto template_t<Template>::operator[](auto&& types) const noexcept
	{
		return apply_template(*this, PP_FORWARD(types));
	}
}
