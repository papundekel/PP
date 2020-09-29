#pragma once
#include <utility>
#include "tuple.hpp"
#include "../value_t.hpp"
#include "../overloaded.hpp"

namespace PP
{
	namespace detail
	{
		template <std::size_t, std::size_t...>
		constexpr inline auto find_index = 0;
		template <std::size_t I, std::size_t H, std::size_t... T>
		constexpr inline auto find_index<I, H, T...> = I == H ? 0 : 1 + find_index<I, T...>;

		template <std::size_t, std::size_t...>
		constexpr inline auto count_smaller_indices = 0;
		template <std::size_t I, std::size_t H, std::size_t... T>
		constexpr inline auto count_smaller_indices<I, H, T...> = I > H ? count_smaller_indices<I, T...> + 1 : count_smaller_indices<I, T...>;

		template <std::size_t current_index, std::size_t... applied_indices>
		constexpr decltype(auto) helper(value_t<current_index>, std::index_sequence<applied_indices...>, auto&& applied_args, auto&& new_args)
		{
			constexpr auto i = find_index<current_index, applied_indices...>;
			if constexpr (i < sizeof...(applied_indices))
				return tuple_get<i>(std::forward<decltype(applied_args)>(applied_args));
			else
				return tuple_get<current_index - count_smaller_indices<current_index, applied_indices...>>
					(std::forward<decltype(new_args)>(new_args));
		}

		template <std::size_t... I>
		constexpr decltype(auto) h(auto&& f, std::index_sequence<I...>, auto applied_indices, auto&& applied_args, auto&& new_args)
		{
			return std::forward<decltype(f)>(f)(helper
				( value_v<I>
				, applied_indices
				, std::forward<decltype(applied_args)>(applied_args)
				, std::forward<decltype(new_args)>(new_args))...);
		}

		template <std::size_t Default, std::size_t...>
		constexpr inline auto apply_partially_helper = std::make_index_sequence<Default>{};
		template <std::size_t Default, std::size_t H, std::size_t... I>
		constexpr inline auto apply_partially_helper<Default, H, I...> = std::index_sequence<H, I...>{};

		template <bool copy_f, bool copy_args, std::size_t... I>
		struct apply_partially_h
		{
			constexpr auto operator()(auto& f, auto&... args) const
			{
				return
					[&f, &args...](auto&&... other_args) constexpr -> decltype(auto)
					{
						return detail::h
							( f
							, std::make_index_sequence<sizeof...(args) + sizeof...(other_args)>{}
							, apply_partially_helper<sizeof...(args), I...>
							, std::forward_as_tuple(args...)
							, std::forward_as_tuple(std::forward<decltype(other_args)>(other_args)...));
					};
			}
		};
		template <std::size_t... I>
		struct apply_partially_h<false, true, I...>
		{
			constexpr auto operator()(auto& f, auto... args) const
			{
				return
					[&f, ...args = std::move(args)](auto&&... other_args) constexpr -> decltype(auto)
					{
						return apply_partially_h<false, false, I...>{}(f, args...)(std::forward<decltype(other_args)>(other_args)...);
					};
			}
		};
		template <std::size_t... I>
		struct apply_partially_h<true, false, I...>
		{
			constexpr auto operator()(auto f, auto&... args) const
			{
				return
					[f = std::move(f), &args...](auto&&... other_args) constexpr -> decltype(auto)
					{
						return apply_partially_h<false, false, I...>{}(f, args...)(std::forward<decltype(other_args)>(other_args)...);
					};
			}
		};
		template <std::size_t... I>
		struct apply_partially_h<true, true, I...>
		{
			constexpr auto operator()(auto f, auto... args) const
			{
				return
					[f = std::move(f), ...args = std::move(args)](auto&&... other_args) constexpr -> decltype(auto)
					{
						return apply_partially_h<false, false, I...>{}(f, args...)(std::forward<decltype(other_args)>(other_args)...);
					};
			}
		};
	}

	template <bool copy_f = true, bool copy_args = true, std::size_t... I>
	constexpr inline auto apply_partially = detail::apply_partially_h<copy_f, copy_args, I...>{};
}
