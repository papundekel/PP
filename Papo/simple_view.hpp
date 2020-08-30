#pragma once
#include <utility>
#include "view.hpp"
#include "compressed_pair.hpp"
#include "unbounded.hpp"
#include "size_t.hpp"

namespace Papo
{
	template <iterator Iterator, sentinel<Iterator> Sentinel = Iterator>
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
		template <view View>
		constexpr simple_view(View&& v)
			: simple_view(Papo::begin(std::forward<View>(v)), Papo::end(std::forward<View>(v)))
		{}
		template <typename T>
		constexpr simple_view(const std::initializer_list<T>& l)
			: simple_view(Papo::begin(l), Papo::end(l))
		{}
		constexpr iterator auto begin() const
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
	template <view View>
	simple_view(View&&) -> simple_view<begin_t<View>, end_t<View>>;

	template <iterator Iterator>
	constexpr view auto operator^(Iterator begin, sentinel<Iterator> auto end)
	{
		return simple_view(begin, end);
	}

	constexpr view auto operator|(view auto&& v, unbounded_t)
	{
		return begin(v) ^ unbounded;
	}
}
