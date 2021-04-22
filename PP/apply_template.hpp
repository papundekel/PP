#pragma once
#include "apply_template_pack.hpp"

#include "functional/apply_partially_first.hpp"
#include "functional/compose.hpp"
#include "functional/functor.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "tuple_apply.hpp"
#include "tuple_get.hpp"
#include "tuple_like.hpp"

namespace PP
{
	PP_FUNCTOR(apply_template, auto Template, concepts::tuple auto&& types)
	{
		return (apply_template_pack * Template)[PP_FORWARD(types)];
	});

	constexpr inline auto apply_template_type = get_type | apply_template;
	constexpr inline auto apply_template_value = get_type_value | apply_template;

	template <template <typename...> typename Template>
	constexpr auto template_t<Template>::operator[](auto&& types) const noexcept
	{
		return apply_template(*this, PP_FORWARD(types));
	}
}
