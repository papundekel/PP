#pragma once
#include "../conditional.hpp"
#include "../declval.hpp"
#include "../functional/apply_partially.hpp"
#include "../get_type.hpp"
#include "../tuple_apply.hpp"
#include "../value_t.hpp"

namespace PP
{
	namespace detail
	{
		PP_FUNCTOR(is_constructible_pack_impl, concepts::value auto Noexcept, concepts::type auto t, concepts::type auto... arg_types)
		{
			return conditional(Noexcept,
				requires
				{
					{ PP_GET_TYPE(t)(declval(arg_types)...) } noexcept;
				},
				requires
				{
					PP_GET_TYPE(t)(declval(arg_types)...);
				});
		});

		PP_FUNCTOR(is_constructible_impl, concepts::value auto Noexcept, concepts::type auto t, concepts::tuple auto arg_tuple)
		{
			return (is_constructible_pack_impl * Noexcept * t)[arg_tuple];
		});
	}

	constexpr inline auto is_constructible_pack = detail::is_constructible_pack_impl * value_false;
	constexpr inline auto is_constructible_noexcept_pack = detail::is_constructible_pack_impl * value_true;

	constexpr inline auto is_constructible = detail::is_constructible_impl * value_false;
	constexpr inline auto is_constructible_noexcept = detail::is_constructible_impl * value_true;

	namespace concepts
	{
		template <typename T, typename... Args>
		concept constructible = is_constructible_pack(PP::type<T>, PP::type<Args>...);
		template <typename T, typename... Args>
		concept constructible_noexcept = is_constructible_noexcept_pack(PP::type<T>, PP::type<Args>...);
	}
}
