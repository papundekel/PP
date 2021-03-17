#pragma once
#include "view.hpp"

namespace PP
{
	template <typename I, typename E, typename J>
	class view_chain_iterator
	{
		I i;
		E e;
		J j;

	public:
		constexpr view_chain_iterator(const I& i, const E& e, const J& j)
			: i(i)
			, e(e)
			, j(j)
		{}

		constexpr decltype(auto) operator*() const
		{
			if (i != e)
				return *i;
			else
				return *j;
		}

		constexpr void step()
		{
			if (i != e)
				++i;
			else
				++j;
		}

		constexpr bool operator==(const view_chain_iterator& other) const
		{
			return i == other.i && e == other.e && j == other.j;
		}
		constexpr bool operator==(const auto& other) const
		{
			if (i != e)
				return false;
			else
				return j == other;
		}
	};

	template <typename I, typename E>
	class view_chain_wrap
	{
		compressed_pair<I, E> pair;

	public:
		constexpr view_chain_wrap(const I& i, const E& e)
			: pair(i, e)
		{}

		constexpr auto begin() const
		{
			return pair.first;
		}
		constexpr auto end() const
		{
			return pair.second;
		}
	};

	constexpr auto view_chain(concepts::view auto&& v)
	{
		return view_chain_wrap(view_begin(PP_FORWARD(v)), view_end(PP_FORWARD(v)));
	}

	template <typename I, typename E>
	constexpr auto operator^(view_chain_wrap<I, E> vc, concepts::view auto&& v)
	{
		return view_chain_wrap(view_chain_iterator(vc.begin(), vc.end(), view_begin(PP_FORWARD(v))), view_end(PP_FORWARD(v)));
	}
}
