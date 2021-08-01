#pragma once
#include <initializer_list>

#include "any_iterator.hpp"
#include "containers/singular.hpp"
#include "containers/tuple_std.hpp"
#include "view/concept.hpp"
#include "view/empty.hpp"

namespace PP
{
template <typename, typename>
class any_view_implementation;

template <typename T>
concept PPany_view = type<T>
->Template == Template<any_view_implementation>;

///
/// @brief A view made of two @ref PP::any_iterator_implementation
///
/// @tparam CategoryT
/// @tparam T
///
template <typename CategoryT, typename T>
class any_view_implementation
{
	template <typename, typename>
	friend class any_view_implementation;

	any_iterator_implementation<CategoryT, CategoryT, T> begin_;
	any_iterator_implementation<CategoryT, CategoryT, T> end_;

public:
	///
	/// @brief Constructs the view from two strongly typed iterators.
	///
	/// @param begin The begin iterator.
	/// @param end The end iterator.
	///
	constexpr any_view_implementation(auto begin, auto end)
	    : begin_(placeholder,
	             detail::make_any_iterator_pointer(begin,
	                                               type<T>,
	                                               make_singular(PP_DT(end))))
	    , end_(placeholder,
	           detail::make_any_iterator_pointer(end,
	                                             type<T>,
	                                             make_singular(PP_DT(begin))))
	{}

	///
	/// @brief Copy constructor from a compatible any_view.
	///
	/// @param other The view to copy.
	///
	/// @tparam CategoryTOther The iterator category of @p other.
	/// @tparam U The type of dereferencing of @p other.
	///
	template <detail::at_least_type<CategoryT> CategoryTOther,
	          concepts::convertible_to<T> U>
	constexpr any_view_implementation(
	    const any_view_implementation<CategoryTOther, U>& other)
	    : begin_(other.begin_)
	    , end_(other.end_)
	{}

	///
	/// @brief Move constructor from a compatible any_view.
	///
	/// @param other The view to move.
	///
	/// @tparam CategoryTOther The iterator category of @p other.
	/// @tparam U The type of dereferencing of @p other.
	///
	template <detail::at_least_type<CategoryT> CategoryTOther,
	          concepts::convertible_to<T> U>
	constexpr any_view_implementation(
	    any_view_implementation<CategoryTOther, U>&& other)
	    : begin_(move(other.begin_))
	    , end_(move(other.end_))
	{}

	///
	/// @brief Constructs the view from an @ref std::initializer_list.
	///
	/// @param list The initializer list.
	///
	constexpr any_view_implementation(
	    const std::initializer_list<PP_GT(~type<T>)>& list)
	    : any_view_implementation(list.begin(), list.end())
	{}

	///
	/// @brief Construct the view from a view of any type.
	///
	/// @param v A view.
	///
	constexpr any_view_implementation(concepts::view auto&& v) requires(
	    !PPany_view<decltype(v)>)
	    : any_view_implementation(view::begin(PP_F(v)), view::end(PP_F(v)))
	{}

	///
	/// @brief Constructs an empty view.
	///
	constexpr any_view_implementation()
	    : any_view_implementation(empty_view<T>{})
	{}

	///
	/// @brief Return the begin iterator.
	///
	/// @return The begin iterator.
	///
	constexpr auto begin() const
	{
		return begin_;
	}

	///
	/// @brief Return the end iterator.
	///
	/// @return The end iterator.
	///
	constexpr auto end() const
	{
		return end_;
	}

	///
	/// @brief Indexes into the view. Same as indexing the begin iterator.
	///
	/// @param index The index.
	/// @return The dereferenced value.
	///
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
constexpr auto min_value_t(concepts::value auto a, concepts::value auto b)
{
	if constexpr (PP_GV(a) <= PP_GV(b))
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
	return any_view<PP_GV(min_iterator_category(PP_DT(begin), PP_DT(end))),
	                decltype(*begin)>(begin, end);
}
}

PP_CIA make_any_view = make_overloaded_pack(
    [](concepts::iterator auto begin, concepts::iterator auto end)
    {
	    return detail::make_any_view(begin, end);
    },
    [](concepts::view auto&& v)
    {
	    return detail::make_any_view(view::begin(PP_F(v)), view::end(PP_F(v)));
    });
}
