#pragma once
#include "dynamic_block.hpp"
#include "no_default_initialized.hpp"
#include "static_block.hpp"
#include "view.hpp"
#include "view_destroy.hpp"
#include "view_copy_uninitialized.hpp"
#include "view_move_uninitialized.hpp"
#include "view_remove.hpp"

namespace PP
{
	template <typename T, size_t StaticCapacity, typename Allocator = std::allocator<T>>
	class small_optimized_vector
	{
		static_block<T, StaticCapacity> block_s;
		dynamic_block<T, Allocator> block_d;
		no_default_initialized<size_t> count_;

		constexpr small_optimized_vector(size_t dynamic_capacity, size_t count, auto&& allocator)
			: block_s()
			, block_d(PP_FORWARD(allocator), dynamic_capacity)
			, count_(count)
		{}

		constexpr small_optimized_vector(placeholder_t, auto&& allocator)
			: small_optimized_vector(0, 0, PP_FORWARD(allocator))
		{}

		constexpr small_optimized_vector(placeholder_t, size_t count, auto&& allocator)
			: small_optimized_vector(count > StaticCapacity ? count : 0, count, PP_FORWARD(allocator))
		{}

		constexpr small_optimized_vector(placeholder_t, concepts::view auto&& view)
			: small_optimized_vector(placeholder, view_count(PP_FORWARD(view)), Allocator())
		{
			view_copy_uninitialized(*this, PP_FORWARD(view));
		}

	public:
		constexpr small_optimized_vector() noexcept(noexcept(Allocator()))
			: small_optimized_vector(placeholder, Allocator())
		{}

		small_optimized_vector(small_optimized_vector&&)
			= default;

		static constexpr auto create_empty_from_allocator(auto&& allocator)
		{
			return small_optimized_vector(placeholder, PP_FORWARD(allocator));
		}
		
		static constexpr auto create_copy_view(concepts::view auto&& view)
		{
			return small_optimized_vector(placeholder, PP_FORWARD(view));
		}

		constexpr ~small_optimized_vector()
		{
			destroy_all();
		}

		small_optimized_vector& operator=(small_optimized_vector&&)
			= default;

		constexpr void push_back(auto&&... args)
		{
			auto c = capacity();

			if (count() == c)
			{
				auto new_block_d = block_d.spawn_new(c != 0 ? 2 * c : 2);

				view_move_uninitialized(new_block_d, *this);

				destroy_all();

				block_d = move(new_block_d);
			}

			construct_at_pack(end(), PP_FORWARD(args)...);

			++count_;
		}

		constexpr T pop_back()
		{
			if (count() == 0)
				throw 0;

			--count_;

			T& back = *end();

			auto temp = PP::move(back);

			back.~T();

			return PP::move(temp);
		}

		constexpr void clear() noexcept
		{
			destroy_all();

			if (!uses_static_block())
				block_d = block_d.spawn_new(0);

			count_ = 0;
		}

		constexpr T* begin() noexcept
		{
			if (uses_static_block())
				return block_s.begin();
			else
				return block_d.begin();
		}
		constexpr const T* begin() const noexcept
		{
			if (uses_static_block())
				return block_s.begin();
			else
				return block_d.begin();
		}
		constexpr T* end() noexcept
		{
			return begin() + count_;
		}
		constexpr const T* end() const noexcept
		{
			return begin() + count_;
		}

		constexpr T& operator[](ptrdiff_t i) noexcept
		{
			return begin()[i];
		}
		constexpr const T& operator[](ptrdiff_t i) const noexcept
		{
			return begin()[i];
		}

		constexpr bool empty() const noexcept
		{
			return count_ == 0;
		}
		constexpr size_t count() const noexcept
		{
			return count_;
		}
		constexpr size_t capacity() const noexcept
		{
			if (uses_static_block())
				return StaticCapacity;
			else
				return block_d.count();
		}

		constexpr void erase_until_end(const T* i) noexcept
		{
			view_destroy(simple_view(i, end()));
			count_ = i - begin();
		}

		constexpr void remove(auto&& predicate)
		{
			auto i = view_remove(PP_FORWARD(predicate), *this);
			erase_until_end(i);
		}

		constexpr T& back() noexcept
		{
			return end()[-1];
		}
		constexpr const T& back() const noexcept
		{
			return end()[-1];
		}

	private:
		constexpr bool uses_static_block() const noexcept
		{
			return block_d.count() == 0;
		}

		constexpr void destroy_all() noexcept
		{
			view_destroy(*this);
		}
	};
}
