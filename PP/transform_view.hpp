#pragma once
#include "apply_template.hpp"
#include "apply_transform.hpp"
//#include "arg_splitter.hpp"
#include "arrow_operator_wrapper.hpp"
#include "compressed_pair.hpp"
#include "concepts/pointer.hpp"
#include "decompose_template.hpp"
#include "get_type.hpp"
#include "in_place_tag.hpp"
#include "iterator_inner.hpp"
#include "ptrdiff_t.hpp"
#include "remove_cvref.hpp"
#include "simple_view.hpp"

namespace PP
{
	constexpr inline struct transform_iterator_in_place_delimiter_t
	{
	} transform_iterator_in_place_delimiter;

	template <typename BaseIterator, typename Transform>
	class transform_iterator
	{
		// static constexpr auto splitter = arg_splitter *
		// type<transform_iterator_in_place_delimiter_t> *
		// type_tuple<BaseIterator, Transform>;

		compressed_pair<BaseIterator, Transform> iterator_transform;

	public:
		constexpr transform_iterator(concepts::iterator auto&& iterator,
									 auto&& transform)
			: iterator_transform(PP_FORWARD(iterator), PP_FORWARD(transform))
		{}
		// constexpr transform_iterator(in_place_tag_t, auto&&... args)
		//	: iterator_transform
		//	(
		//		splitter(value_0, PP_FORWARD(args)...),
		//		splitter(value_1, PP_FORWARD(args)...)
		//	)
		//{}

		constexpr decltype(auto) operator*() const
		{
			return iterator_transform.second(*iterator_transform.first);
		}
		constexpr auto operator->() const
		{
			return make_arrow_operator_wrapper(
				[this]()
				{
					return **this;
				});
		}
		constexpr void step()
		{
			++iterator_transform.first;
		}
		constexpr auto step_back()
		{
			if constexpr (PP::concepts::iterator_bi<BaseIterator>)
				--iterator_transform.first;
			else
				return 0;
		}
		constexpr auto advance(ptrdiff_t offset)
		{
			if constexpr (PP::concepts::iterator_ra<BaseIterator>)
				iterator_transform.first += offset;
			else
				return 0;
		}
		constexpr auto operator==(const auto& other) const
		{
			return iterator_transform.first == PP::iterator_inner(other);
		}
		constexpr auto operator-(const transform_iterator& other) const
		{
			if constexpr (PP::concepts::iterator_ra<BaseIterator>)
				return iterator_transform.first -
					   other.iterator_transform.first;
			else
				return ptrdiff_t(0);
		}
		constexpr auto operator-(const auto& other) const
		{
			return iterator_transform.first - PP::iterator_inner(other);
		}
		constexpr decltype(auto) operator[](ptrdiff_t offset) const
		{
			if constexpr (PP::concepts::iterator_ra<BaseIterator>)
				return iterator_transform.second(
					iterator_transform.first[offset]);
		}
		constexpr auto inner_iterator() const
		{
			return iterator_transform.first;
		}
	};
	template <typename I, typename T>
	transform_iterator(I&& i, T&& t)
		-> transform_iterator<PP_GET_TYPE(~type<I>), PP_GET_TYPE(~type<T>)>;

	template <typename Functor>
	struct transform
	{
		Functor functor;
	};

	constexpr auto transform_view(concepts::view auto&& v, auto&& f)
	{
		return transform_iterator(view_begin(PP_FORWARD(v)), PP_FORWARD(f)) ^
			   transform_iterator(view_end(PP_FORWARD(v)), PP_FORWARD(f));
	}

	constexpr auto operator&(concepts::iterator auto&& i, transform<auto> t)
	{
		return transform_iterator(PP_FORWARD(i), move(t).functor);
	}

	constexpr auto operator||(concepts::view auto&& v, transform<auto> t)
	{
		return begin(PP_FORWARD(v)) & move(t) ^ end(PP_FORWARD(v));
	}

	constexpr auto operator|(concepts::view auto&& v, transform<auto> t)
	{
		return transform_view(PP_FORWARD(v), move(t).functor);
	}
}
