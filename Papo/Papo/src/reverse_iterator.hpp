#pragma once
#include "enable_if.hpp"
#include "int.hpp"
#include "is_iterator_bi.hpp"
#include "is_iterator_ra.hpp"

template <typename it, typename = enable_if<is_iterator_bi<it>>>
class reverse_iterator
{
	it i;
public:
	reverse_iterator(it i)
		: i(i)
	{}
	decltype(auto) operator->() const
	{
		return i->;
	}
	decltype(auto) operator*()
	{
		return *i;
	}
	decltype(auto) operator[](diff_t offset) const
	{
		static_assert(is_iterator_ra<it>);
		return i[-offset];
	}
	reverse_iterator& operator++()
	{
		--i;
		return *this;
	}
	reverse_iterator operator++(int)
	{
		auto temp = *this;
		++i;
		return temp;
	}
	reverse_iterator& operator--()
	{
		--i;
		return *this;
	}
	reverse_iterator operator--(int)
	{
		auto temp = *this;
		--i;
		return temp;
	}
	reverse_iterator operator+(diff_t other) const
	{
		static_assert(is_iterator_ra<it>);
		return i - other;
	}
	reverse_iterator operator-(diff_t other) const
	{
		static_assert(is_iterator_ra<it>);
		return i + other;
	}
	diff_t operator-(reverse_iterator other) const
	{
		static_assert(is_iterator_ra<it>);
		return i - other.i;
	}
	template <typename it2>
	bool operator==(reverse_iterator<it2> other) const
	{
		return i == other.i;
	}
	template <typename it2>
	bool operator!=(reverse_iterator<it2> other) const
	{
		return i != other.i;
	}
	bool operator<(reverse_iterator other) const
	{
		return i < other.i;
	}
};