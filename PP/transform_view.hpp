#pragma once
#include "simple_view.hpp"

namespace PP
{
	template <iterator BaseIterator, typename Transform>
	class transform_iterator
	{
		compressed_pair<BaseIterator, Transform> pair;
	public:
		constexpr transform_iterator(BaseIterator base_iterator, Transform&& t)
			: pair{ base_iterator, std::move(t) }
		{}
		constexpr transform_iterator(BaseIterator base_iterator, const Transform& t)
			: pair{ base_iterator, t }
		{}
		constexpr decltype(auto) operator*() const
		{
			return pair.second(*pair.first);
		}
		constexpr decltype(auto) operator->() const
		{
			return &operator*();
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
		constexpr auto operator-(const transform_iterator& other) const
		{
			return pair.first - other.pair.first;
		}
		constexpr decltype(auto) operator[](std::size_t index) const
		{
			return pair.second(pair.first[index]);
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
		Functor functor;
		template <typename F>
		constexpr transform(F&& f)
			: functor(std::forward<F>(f))
		{}
	};
	template <typename F>
	transform(F&&)->transform<std::remove_cvref_t<F>>;

	template <typename F>
	constexpr view auto transform_view(view auto&& v, F&& f)
	{
		return transform_iterator(begin(v), std::forward<F>(f)) ^ transform_iterator(end(v), std::forward<F>(f));
	}

	constexpr iterator auto operator&(iterator auto i, transform<auto> t)
	{
		return transform_iterator(i, std::move(t).functor);
	}

	template <view View>
	constexpr view auto operator||(View&& v, transform<auto> t)
	{
		return begin(std::forward<View>(v)) & std::move(t) ^ end(std::forward<View>(v));
	}

	template <view View>
	constexpr view auto operator|(View&& v, transform<auto> t)
	{
		return transform_view(std::forward<View>(v), std::move(t).functor);
	}
}
