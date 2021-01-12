#pragma once
#include <utility>
#include <initializer_list>
#include "view.hpp"
#include "compressed_pair.hpp"
#include "unbounded.hpp"
#include "size_t.hpp"
#include "concepts/same_except_cvref.hpp"

namespace PP
{
	template <typename Iterator, concepts::sentinel<Iterator> Sentinel = Iterator>
	class simple_view
	{
		compressed_pair<Iterator, Sentinel> pair;

	public:
		constexpr simple_view()
			: pair()
		{}
		constexpr simple_view(Iterator begin, Sentinel end)
			: pair{ begin, end }
		{}
		constexpr simple_view(concepts::view auto&& v)
		requires (!same_except_cvref(type_v<simple_view>, PP_DECLTYPE(v)))
			: simple_view(begin(PP_FORWARD(v)), end(PP_FORWARD(v)))
		{}
		constexpr simple_view(const std::initializer_list<apply_transform_t<remove_reference | iterator_base, Iterator>>& l)
			: simple_view(l.begin(), l.end())
		{}
		constexpr auto begin() const
		{
			return pair.first;
		}
		constexpr auto end() const
		{
			return pair.second;
		}
		constexpr decltype(auto) operator[](size_t index) const
		{
			return begin()[index];
		}
	};
	simple_view(concepts::view auto&& v) -> simple_view<PP_APPLY_TRANSFORM(view_begin_iterator, v), PP_APPLY_TRANSFORM(view_end_iterator, v)>;
	template <typename T>
	simple_view(const std::initializer_list<T>&) -> simple_view<const T*, const T*>;

	constexpr concepts::view auto operator^(auto begin, concepts::sentinel<decltype(begin)> auto end)
	{
		return simple_view(begin, end);
	}

	constexpr concepts::view auto operator|(concepts::view auto&& v, unbounded_t)
	{
		return begin(PP_FORWARD(v)) ^ unbounded;
	}

	constexpr concepts::view auto operator>>(std::size_t offset, concepts::view auto&& v)
	{
		return simple_view(begin(PP_FORWARD(v)) + offset, end(PP_FORWARD(v)));
	}
}
