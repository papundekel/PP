#pragma once
#include <initializer_list>

#include "any_iterator.hpp"
#include "empty_view.hpp"
#include "singular_tuple.hpp"
#include "tuple_std.hpp"
#include "view.hpp"

namespace PP
{
	template <typename, typename>
	class any_view_implementation;

	template <typename T>
	concept PPany_view = type<T>->Template == Template<any_view_implementation>;

	template <typename CategoryT, typename T>
	class any_view_implementation
	{
		template <typename, typename>
		friend class any_view_implementation;

		any_iterator_implementation<CategoryT, CategoryT, T> begin_;
		any_iterator_implementation<CategoryT, CategoryT, T> end_;

	public:
		constexpr any_view_implementation(auto begin, auto end)
			: begin_(placeholder,
					 detail::make_any_iterator_pointer(
						 begin,
						 type<T>,
						 make_singular_tuple(PP_DECLTYPE(end))))
			, end_(placeholder,
				   detail::make_any_iterator_pointer(
					   end,
					   type<T>,
					   make_singular_tuple(PP_DECLTYPE(begin))))
		{}

		template <detail::at_least_type<CategoryT> CategoryTOther,
				  concepts::convertible_to<T> U>
		constexpr any_view_implementation(
			const any_view_implementation<CategoryTOther, U>& other)
			: begin_(other.begin_)
			, end_(other.end_)
		{}
		template <detail::at_least_type<CategoryT> CategoryTOther,
				  concepts::convertible_to<T> U>
		constexpr any_view_implementation(
			any_view_implementation<CategoryTOther, U>&& other)
			: begin_(move(other.begin_))
			, end_(move(other.end_))
		{}

		constexpr any_view_implementation(
			const std::initializer_list<PP_GET_TYPE(~type<T>)>& list)
			: any_view_implementation(list.begin(), list.end())
		{}
		constexpr any_view_implementation(concepts::view auto&& v) requires(
			!PPany_view<decltype(v)>)
			: any_view_implementation(view_begin(PP_FORWARD(v)),
									  view_end(PP_FORWARD(v)))
		{}
		constexpr any_view_implementation()
			: any_view_implementation(empty_view<T>{})
		{}

		constexpr auto begin() const
		{
			return begin_;
		}
		constexpr auto end() const
		{
			return end_;
		}

		constexpr decltype(auto) operator[](ptrdiff_t index) const
		{
			if constexpr (-type<CategoryT> == iterator_category::ra)
				return begin()[index];
		}
	};
	template <typename T>
	any_view_implementation(const std::initializer_list<T>&)
		-> any_view_implementation<value_t<iterator_category::ra>, const T&>;
	template <typename T, size_t N>
	any_view_implementation(T (&)[N])
		-> any_view_implementation<value_t<iterator_category::ra>, T&>;

	template <iterator_category Category, typename T>
	using any_view = any_view_implementation<value_t<Category>, T>;

	namespace detail
	{
		constexpr auto min_value_t(concepts::value auto a,
								   concepts::value auto b)
		{
			if constexpr (PP_GET_VALUE(a) <= PP_GET_VALUE(b))
				return a;
			else
				return b;
		}
		constexpr auto min_iterator_category(concepts::type auto a,
											 concepts::type auto b)
		{
			return min_value_t(get_iterator_category_value_t(a),
							   get_iterator_category_value_t(b));
		}

		constexpr auto make_any_view(concepts::iterator auto begin,
									 concepts::iterator auto end)
		{
			return any_view<PP_GET_VALUE(
								min_iterator_category(PP_DECLTYPE(begin),
													  PP_DECLTYPE(end))),
							decltype(*begin)>(begin, end);
		}
	}

	constexpr inline auto make_any_view = make_overloaded_pack(
		[](concepts::iterator auto begin, concepts::iterator auto end)
		{
			return detail::make_any_view(begin, end);
		},
		[](concepts::view auto&& v)
		{
			return detail::make_any_view(view_begin(PP_FORWARD(v)),
										 view_end(PP_FORWARD(v)));
		});
}
