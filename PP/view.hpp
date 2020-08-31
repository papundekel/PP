#pragma once
#include <utility>
#include <type_traits>
#include "size_t.hpp"
#include "iterator.hpp"

namespace Papo
{
	namespace detail
	{
		template <typename T>
		concept has_begin = requires (T t)
		{
			{ t.begin() } -> iterator;
		};
		template <typename T>
		concept has_end = requires (T t)
		{
			t.end();
		};
	}
	template <detail::has_begin View>
	constexpr iterator auto begin(View&& v)
	{
		return std::forward<View>(v).begin();
	}
	template <detail::has_end View>
	constexpr auto end(View&& v)
	{
		return std::forward<View>(v).end();
	}

	namespace detail
	{
		template <typename View>
		using begin_t = decltype(begin(std::declval<View>()));
	}

	template <typename View>
	concept view = requires (View v)
	{
		{ begin(v) } -> iterator;
		{ end(v) } -> sentinel<detail::begin_t<View>>;
	};

	namespace detail
	{
		// workaround
		template <typename T>
		concept is_size_t = same<T, size_t>;

		template <typename T>
		concept view_with_count =
			view<T> &&
			requires (const T t)
			{
				{ t.count() } -> is_size_t;
				// { t.count() } -> same<size_t>; // doesn't compile
			};
	}
	template <view View>
	constexpr size_t count(View&& v)
	{
		return end(std::forward<View>(v)) - begin(std::forward<View>(v));
	}
	template <detail::view_with_count View>
	constexpr size_t count(View&& v)
	{
		return std::forward<View>(v).count();
	}

	template <view View>
	constexpr bool empty(View&& v)
	{
		return begin(std::forward<View>(v)) == end(std::forward<View>(v));
	}

	template <view View>
	using begin_t = detail::begin_t<View>;
	template <view View>
	using end_t = decltype(end(std::declval<View>()));
	template <iterator Iterator>
	using iterator_base_t = decltype(*std::declval<Iterator>());
	template <view View>
	using view_base_t = iterator_base_t<begin_t<View>>;
	
	namespace detail
	{
		template <typename T>
		struct initializer_list_wrapper
		{
			std::initializer_list<T> x;

			constexpr auto begin() const
			{
				return x.begin();
			}
			constexpr auto end() const
			{
				return x.end();
			}
			constexpr auto size() const
			{
				return x.size();
			}
		};
		template <typename T>
		constexpr auto& wrap_initializer_list(const std::initializer_list<T>& l)
		{
			return reinterpret_cast<const initializer_list_wrapper<T>&>(l);
		}
	}
}
