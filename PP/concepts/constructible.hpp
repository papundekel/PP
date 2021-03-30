#pragma once
#include "../conditional.hpp"
#include "../declval.hpp"
#include "../functional/apply_partially.hpp"
#include "../get_type.hpp"
#include "../tuple_apply.hpp"
#include "../value_t.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		constexpr T&& declval___() noexcept;

		template <typename T, typename... Args>
		concept constructible = requires
		{
			T(declval___<Args>()...);
		};
		template <typename T, typename... Args>
		concept constructible_noexcept = requires
		{
			{ T(declval___<Args>()...) } noexcept;
		};
	}

	namespace detail
	{
		PP_FUNCTOR(is_constructible_pack_impl, concepts::value auto Noexcept, concepts::type auto t, concepts::type auto... arg_types)
		{
			if constexpr (PP_GET_VALUE(Noexcept))
				return concepts::constructible_noexcept<PP_GET_TYPE(t), PP_GET_TYPE(arg_types)...>;
			else
				return concepts::constructible<PP_GET_TYPE(t), PP_GET_TYPE(arg_types)...>;
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
}
