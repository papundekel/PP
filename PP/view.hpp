#pragma once
//#include <bit>

#include "apply_transform.hpp"
#include "concepts/array.hpp"
#include "declval.hpp"
#include "functional/functor.hpp"
#include "iterator.hpp"
#include "remove_reference.hpp"
#include "size_t.hpp"
#include "tuple_std.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept view_concept_begin_member = requires
		{
			{
				declval(type<T>).begin()
				} -> concepts::iterator;
		};
		template <typename T>
		concept view_concept_begin_array_reference =
			view_concept_begin_member<T> ||
			(is_array <<= remove_reference <<= type<T>);
		template <typename T>
		concept view_concept_begin_any =
			view_concept_begin_array_reference<T> || requires
		{
			{
				begin(declval(type<T>))
				} -> concepts::iterator;
		};

		template <typename T>
		concept view_concept_end_member = requires
		{
			{
				declval(type<T>).end()
				} -> concepts::non_void;
		};
		template <typename T>
		concept view_concept_end_bounded_array_reference =
			view_concept_end_member<T> ||
			(is_bounded_array <<= remove_reference <<= type<T>);
		template <typename T>
		concept view_concept_end_any =
			view_concept_end_bounded_array_reference<T> || requires
		{
			{
				end(declval(type<T>))
				} -> concepts::non_void;
		};
	}

	PP_FUNCTOR(view_begin, detail::view_concept_begin_any auto&& v)
		-> decltype(auto)
	{
		if constexpr (detail::view_concept_begin_member<decltype(v)>)
			return PP_FORWARD(v).begin();
		else if constexpr (detail::view_concept_begin_array_reference<
							   decltype(v)>)
			return v + 0;
		else
			return begin(PP_FORWARD(v));
	});
	PP_FUNCTOR(view_end, detail::view_concept_end_any auto&& v)
		-> decltype(auto)
	{
		if constexpr (detail::view_concept_end_member<decltype(v)>)
			return PP_FORWARD(v).end();
		else if constexpr (detail::view_concept_end_bounded_array_reference<
							   decltype(v)>)
			return v + sizeof(v) / sizeof(*v);
		else
			return end(PP_FORWARD(v));
	});

	namespace detail
	{
		PP_FUNCTOR(view_type_begin_iterator_pure, concepts::type auto v)
		{
			return PP_DECLTYPE(view_begin(declval(v)));
		});
	}

	PP_FUNCTOR(is_view, concepts::type auto t)
	{
		return requires
		{
			{
				view_begin(declval(t))
				} -> concepts::iterator;
			{
				view_end(declval(t))
				} -> concepts::sentinel<PP_APPLY_TRANSFORM(
					detail::view_type_begin_iterator_pure,
					t)>;
		};
	});

	PP_CONCEPT1(view)

	constexpr size_t view_count(concepts::view auto&& v)
	{
		if constexpr (requires
					  {
						  PP_FORWARD(v).count();
					  })
			return PP_FORWARD(v).count();
		else
			return view_end(PP_FORWARD(v)) - view_begin(PP_FORWARD(v));
	}

	constexpr bool view_empty(concepts::view auto&& v)
	{
		return view_begin(PP_FORWARD(v)) == view_end(PP_FORWARD(v));
	}

	PP_FUNCTOR(view_type_begin_iterator, concepts::type auto v)
	{
		return detail::view_type_begin_iterator_pure(v);
	});
	PP_FUNCTOR(view_begin_iterator, concepts::view auto&& v)
	{
		return view_type_begin_iterator(PP_DECLTYPE(v));
	});
	PP_FUNCTOR(view_type_end_iterator, concepts::type auto v)
	{
		return PP_DECLTYPE(view_end(declval(v)));
	});
	PP_FUNCTOR(view_end_iterator, concepts::view auto&& v)
	{
		return view_type_end_iterator(PP_DECLTYPE(v));
	});
	constexpr inline auto view_type_base =
		iterator_base | view_type_begin_iterator;

	namespace detail
	{
		template <typename T>
		struct initializer_list_wrapper
			: public std::initializer_list<T>
		{};
		template <typename T>
		constexpr decltype(auto) wrap_initializer_list(
			const std::initializer_list<T>& l)
		{
			return reinterpret_cast<const initializer_list_wrapper<T>&>(l);
			// return std::bit_cast<initializer_list_wrapper<T>>(l);
		}
	}

	PP_FUNCTOR(view_begin_end, concepts::view auto&& v)
	{
		return make_tuple(view_begin(PP_FORWARD(v)), view_end(PP_FORWARD(v)));
	});
}
