#pragma once
#include "construct_at_pack.hpp"
#include "dynamic_block.hpp"
#include "view.hpp"
#include "view_destroy.hpp"

namespace PP
{
	template <typename T, typename Allocator>
	class simple_vector
	{
		static constexpr size_t default_capacity = 16;

		dynamic_block<T, Allocator> block;
		size_t count_;

		constexpr void destroy_all() noexcept
		{
			view_destroy(*this);
		}

	public:
		explicit constexpr simple_vector(auto&& allocator, size_t capacity) noexcept
			: block(PP_FORWARD(allocator), capacity)
			, count_(0)
		{}
		explicit constexpr simple_vector(auto&& allocator, concepts::view auto&& v)
			: block(PP_FORWARD(allocator), PP_FORWARD(v))
			, count_(block.count())
		{}

		explicit constexpr simple_vector(auto&& allocator) noexcept
			: simple_vector(PP_FORWARD(allocator), default_capacity)
		{}

		constexpr ~simple_vector()
		{
			destroy_all();
		}

		constexpr void push_back(auto&& value)
		{
			if (count() == capacity())
			{
				dynamic_block<T> new_block(2 * capacity());

				view_move_uninitialized(new_block, *this);

				destroy_all();

				block = move(new_block);
			}

			construct_at_pack(end(), PP_FORWARD(value));

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

		constexpr size_t count() const noexcept
		{
			return count_;
		}
		constexpr size_t capacity() const noexcept
		{
			return block.count();
		}
	};
}
