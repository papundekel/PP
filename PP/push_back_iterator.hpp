#pragma once
#include "utility/forward.hpp"

namespace PP
{
	template <typename C>
	class push_back_iterator
	{
		C* c;

	public:
		constexpr push_back_iterator() noexcept
			: c(nullptr)
		{}
		constexpr push_back_iterator(C& c) noexcept
			: c(&c)
		{}

		constexpr push_back_iterator& operator*() noexcept
		{
			return *this;
		}
		constexpr push_back_iterator& operator++() noexcept
		{
			return *this;
		}
		constexpr push_back_iterator operator++(int) noexcept
		{
			return *this;
		}
		constexpr push_back_iterator& operator=(auto&& value)
		{
			c->push_back(PP_FORWARD(value));

			return *this;
		}
		constexpr bool operator==(push_back_iterator other) const noexcept
		{
			return c == other.c;
		}
	};
}