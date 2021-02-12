#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>
#include <memory>
#include "dynamic_block.hpp"
#include "view.hpp"

namespace PP
{
	template <typename T>
	class simple_vector
	{
		static constexpr size_t default_capacity = 16;

		dynamic_block<T> block;
		size_t count_;

		constexpr void destroy_all() noexcept
		{
			std::destroy(begin(), end());
		}

	public:
		explicit constexpr simple_vector(concepts::view auto&& v)
			: block(PP_FORWARD(v))
			, count_(block.count())
		{}
		explicit constexpr simple_vector(std::size_t capacity) noexcept
			: block(capacity)
			, count_(0)
		{}
		constexpr simple_vector() noexcept
			: simple_vector(default_capacity)
		{}

		constexpr ~simple_vector()
		{
			destroy_all();
		}

		template <typename U>
		constexpr void push_back(U&& value)
		{
			if (count() == capacity())
			{
				dynamic_block<T> new_block(2 * capacity());

				std::uninitialized_move(begin(), end(), new_block.begin());

				destroy_all();

				block = std::move(new_block);
			}

			std::construct_at(end(), std::forward<U>(value));

			++count_;
		}

		constexpr void clear() noexcept
		{
			destroy_all();
			block = dynamic_block<T>(default_capacity);
			count_ = 0;
		}

		constexpr T* begin() noexcept
		{
			return block.begin();
		}
		constexpr T* end() noexcept
		{
			return begin() + count_;
		}
		constexpr const T* begin() const noexcept
		{
			return block.begin();
		}
		constexpr const T* end() const noexcept
		{
			return begin() + count_;
		}

		constexpr std::size_t count() const noexcept
		{
			return count_;
		}
		constexpr std::size_t capacity() const noexcept
		{
			return block.count();
		}
	};
}
