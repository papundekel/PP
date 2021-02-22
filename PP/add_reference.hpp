#pragma once
#include "concepts/atomic/referencable.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "ref_qualifier.hpp"

namespace PP
{
	PP_FUNCTOR(add_reference, concepts::value auto ref, concepts::type auto t)
	{
		using T = PP_GET_TYPE(t);

		constexpr auto REF = *PP_COPY_VALUE(ref);

		if constexpr (is_referencable(type<T>))
		{
			if constexpr (REF == ref_qualifier::lvalue)
				return type<T&>;
			else if constexpr (REF == ref_qualifier::rvalue)
				return type<T&&>;
			else
				return t;
		}
		else
			return t;
	});

	template <ref_qualifier ref> struct add_reference_tag_t : public value_t<ref> {};

	constexpr inline add_reference_tag_t<ref_qualifier::lvalue> add_lvalue_tag{};
	constexpr inline add_reference_tag_t<ref_qualifier::rvalue> add_rvalue_tag{};

	template <ref_qualifier ref>
	constexpr auto operator+(concepts::type auto t, add_reference_tag_t<ref> tag) noexcept
	{
		return add_reference(tag, t);
	}
}
