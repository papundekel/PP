#pragma once
#include "compressed_pair.hpp"
#include "placeholder.hpp"
#include "utility/move.hpp"

#include <iostream>

namespace PP
{
	constexpr inline struct scoped_in_place_tag_t {} scoped_in_place_tag;

	template <typename T, typename Destructor>
	class scoped
	{
		template <typename U, typename D>
		friend class scoped;

		compressed_pair<T, Destructor> pair;

	public:
		scoped() = default;

		constexpr scoped(const scoped& other)
			: pair(other.pair.first, other.pair.second)
		{}
		template <typename U, typename D>
		constexpr scoped(const scoped<U, D>& other)
			: pair(other.pair.first, other.pair.second)
		{}
		constexpr scoped(scoped&& other)
			: pair(move(other).pair.first, move(other).pair.second)
		{}
		template <typename U, typename D>
		constexpr scoped(scoped<U, D>&& other)
			: pair(move(other).pair.first, move(other).pair.second)
		{}

		constexpr scoped(placeholder_t, auto&& value, auto&& destructor)
			: pair(PP_FORWARD(value), PP_FORWARD(destructor))
		{}
		constexpr scoped(scoped_in_place_tag_t, auto&&... args)
			: pair(T(PP_FORWARD(args)...), Destructor())
		{}

		constexpr T& get_object()
		{
			return pair.first;
		}
		constexpr const T& get_object() const
		{
			return pair.first;
		}
		constexpr Destructor& get_destructor()
		{
			return pair.second;
		}
		constexpr const Destructor& get_destructor() const
		{
			return pair.second;
		}
	private:
		constexpr void destroy()
		{
			get_destructor()(get_object());
		}
	public:
		template <typename U, typename D>
		constexpr scoped& operator=(const scoped<U, D>& other)
		{
			destroy();
			pair.first = other.pair.first;
			pair.second = other.pair.second;
			return *this;
		}
		template <typename U, typename D>
		constexpr scoped& operator=(scoped<U, D>&& other)
		{
			destroy();
			pair.first = move(other).pair.first;
			pair.second = move(other).pair.second;
			return *this;
		}
		constexpr ~scoped()
		{
			destroy();
		}
	};
	scoped(auto&& v, auto&& d) -> scoped<PP_GET_TYPE(~PP_DECLTYPE(v)), PP_GET_TYPE(~PP_DECLTYPE(d))>;
}
