#pragma once
#include "apply_template.hpp"
#include "apply_transform.hpp"
#include "arrow_operator_wrapper.hpp"
#include "compressed_pair.hpp"
#include "concepts/pointer.hpp"
#include "decompose_template.hpp"
#include "get_type.hpp"
#include "iterator_inner.hpp"
#include "ptrdiff_t.hpp"
#include "remove_cvref.hpp"
#include "simple_view.hpp"

namespace PP
{
	template <typename BaseIterator, typename Transform>
	class transform_iterator
	{
		compressed_pair<BaseIterator, Transform> iterator_transform;

	public:
		constexpr transform_iterator(concepts::iterator auto&& iterator, auto&& transform)
			: iterator_transform(PP_FORWARD(iterator), PP_FORWARD(transform))
		{}

		constexpr decltype(auto) operator*() const
		{
			return iterator_transform.second(*iterator_transform.first);
		}
		constexpr auto operator->() const
		{
			return arrow_operator_wrapper(**this);
		}
		constexpr auto& operator+=(ptrdiff_t offset)
		{
			iterator_transform.first += offset;
			return *this;
		}
		constexpr auto& operator-=(ptrdiff_t offset)
		{
			iterator_transform.first -= offset;
			return *this;
		}
		constexpr auto operator==(const transform_iterator& other) const
		{
			return iterator_transform.first == other.iterator_transform.first;
		}
		constexpr auto operator==(const auto& other) const
		{
			return iterator_transform.first == PP::iterator_inner(other);
		}
		constexpr auto operator-(const transform_iterator& other) const
		{
			return iterator_transform.first - other.iterator_transform.first;
		}
		constexpr auto operator-(const auto& other) const
		{
			return iterator_transform.first - PP::iterator_inner(other);
		}
		constexpr decltype(auto) operator[](ptrdiff_t offset) const
		{
			return iterator_transform.second(iterator_transform.first[offset]);
		}
		constexpr auto inner_iterator() const
		{
			return iterator_transform.first;
		}
	};
	template <typename I, typename T>
	transform_iterator(I&& i, T&& t)->transform_iterator<PP_GET_TYPE(~type<I>), PP_GET_TYPE(~type<T>)>;

	template <typename Functor>
	struct transform
	{
		Functor functor;
	};

	constexpr auto transform_view(concepts::view auto&& v, auto&& f)
	{
		return
			transform_iterator(view_begin(PP_FORWARD(v)), PP_FORWARD(f)) ^
			transform_iterator(view_end  (PP_FORWARD(v)), PP_FORWARD(f));
	}

	constexpr auto operator&(concepts::iterator auto&& i, transform<auto> t)
	{
		return transform_iterator(PP_FORWARD(i), PP_FORWARD(t.functor));
	}

	constexpr auto operator||(concepts::view auto&& v, transform<auto> t)
	{
		return begin(PP_FORWARD(v)) & move(t) ^ end(PP_FORWARD(v));
	}

	constexpr auto operator|(concepts::view auto&& v, transform<auto> t)
	{
		return transform_view(PP_FORWARD(v), PP_FORWARD(t.functor));
	}
}
