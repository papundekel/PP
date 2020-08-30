#pragma once
#include "simple_view.hpp"

namespace Papo
{
	template <iterator BaseIterator, typename Transform>
	class transform_iterator
	{
		compressed_pair<BaseIterator, Transform> pair;
	public:
		constexpr transform_iterator(BaseIterator base_iterator, Transform t)
			: pair{ base_iterator, t }
		{}
		constexpr decltype(auto) operator*() const
		{
			return pair.second(*pair.first);
		}
		constexpr auto& operator+=(size_t offset)
		{
			pair.first += offset;
			return *this;
		}
		constexpr auto& operator-=(size_t offset)
		{
			pair.first -= offset;
			return *this;
		}
		constexpr auto operator==(iterator auto other) const
		{
			return pair.first == other;
		}
		constexpr auto& base()
		{
			return pair.first;
		}
		constexpr auto base() const
		{
			return pair.first;
		}
	};

	template <typename Functor>
	struct transform
	{
		Functor&& functor;
		constexpr transform(Functor&& functor)
			: functor(std::forward<Functor>(functor))
		{}
	};

	constexpr view auto transform_view(view auto&& v, auto f)
	{
		return transform_iterator(begin(v), f) ^ transform_iterator(end(v), f);
	}

	constexpr iterator auto operator&(iterator auto i, transform<auto> t)
	{
		return transform_iterator(i, t.functor);
	}

	template <view View>
	constexpr view auto operator||(View&& v, transform<auto> t)
	{
		return begin(std::forward<View>(v)) & t ^ end(std::forward<View>(v));
	}

	template <view View>
	constexpr view auto operator|(View&& v, transform<auto> t)
	{
		return transform_view(std::forward<View>(v), t.functor);
	}
}
