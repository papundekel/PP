#pragma once
#include <exception>

#include "construct_at_pack.hpp"
#include "destroy_at.hpp"
#include "movable.hpp"
#include "no_default_initialized.hpp"
#include "static_block.hpp"
#include "view/copy_uninitialized.hpp"
#include "view/destroy.hpp"
#include "view/move_uninitialized.hpp"

#include "PP/utility/forward.hpp"
#include "PP/utility/move.hpp"

namespace PP
{
template <typename T, size_t Capacity, bool looping = false>
class array_vector
{
	static_block<T, Capacity> block;
	no_default_initialized<size_t> count_;

	constexpr void destroy_all() noexcept
	{
		view_destroy(*this);
	}

public:
	constexpr array_vector() noexcept
	    : block()
	    , count_(0)
	{}

	constexpr array_vector(const array_vector& other)
	    : block()
	    , count_(other.count_)
	{
		view_copy_uninitialized(*this, other);
	}
	constexpr array_vector(array_vector&& other)
	    : block()
	    , count_(other.count_)
	{
		view_move_uninitialized(*this, other);
		other.destroy_all();
		other.count_ = 0;
	}
	constexpr ~array_vector()
	{
		destroy_all();
	}

	constexpr T* begin() noexcept
	{
		return block.begin();
	}
	constexpr const T* begin() const noexcept
	{
		return block.begin();
	}
	constexpr T* end() noexcept
	{
		return block.begin() + count();
	}
	constexpr const T* end() const noexcept
	{
		return block.begin() + count();
	}

	constexpr bool empty() const noexcept
	{
		return count() == 0;
	}

	constexpr size_t count() const noexcept
	{
		return count_;
	}

	constexpr void clear() noexcept
	{
		destroy_all();
		count_ = 0;
	}

	constexpr void push_back(auto&&... args)
	{
		if (count() == Capacity)
		{
			if constexpr (!looping)
				std::terminate();
			else
				clear();
		}

		construct_at_pack(end(), PP_F(args)...);
		++count_;
	}

	constexpr void pop_back() noexcept
	{
		if (!empty())
		{
			--count_;
			destroy_at(end());
		}
		else
		{
			if constexpr (!looping)
				std::terminate();
		}
	}

	constexpr T& operator[](ptrdiff_t i) noexcept
	{
		return begin()[i];
	}
	constexpr const T& operator[](ptrdiff_t i) const noexcept
	{
		return begin()[i];
	}
};
}
