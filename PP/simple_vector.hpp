#pragma once
#include "construct_at_pack.hpp"
#include "dynamic_block.hpp"
#include "view.hpp"
#include "view_destroy.hpp"
#include "view_move_uninitialized.hpp"
#include "view_remove.hpp"

namespace std
{
	template <typename T>
	struct allocator;
}

namespace PP
{
	template <typename T, typename Allocator = std::allocator<T>>
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
		constexpr simple_vector(auto&& allocator, size_t capacity) noexcept
			: block(PP_FORWARD(allocator), capacity)
			, count_(0)
		{}
		constexpr simple_vector(auto&& allocator, concepts::view auto&& v)
			: block(PP_FORWARD(allocator), PP_FORWARD(v))
			, count_(block.count())
		{}
		explicit constexpr simple_vector(size_t capacity) noexcept
			: simple_vector(Allocator(), capacity)
		{}
		explicit constexpr simple_vector(concepts::view auto &&v)
			: simple_vector(Allocator(), PP_FORWARD(v))
		{}
		constexpr simple_vector(placeholder_t, auto&& allocator) noexcept
			: simple_vector(PP_FORWARD(allocator), default_capacity)
		{}
		constexpr simple_vector(placeholder_t, size_t count) noexcept
			: simple_vector(count)
		{
			view_for_each([](T& t) { construct_at_pack(&t); }, *this);
		}
		constexpr simple_vector() noexcept
			: simple_vector(Allocator(), default_capacity)
		{}

		simple_vector(simple_vector&&) = default;
		simple_vector& operator=(simple_vector&&) = default;

		constexpr ~simple_vector()
		{
			destroy_all();
		}

		constexpr void push_back(auto&&... args)
		{
			auto c = capacity();

			if (count() == c)
			{
				auto new_block = block.spawn_new(c != 0 ? 2 * c : 2);

				view_move_uninitialized(new_block, *this);

				destroy_all();

				block = move(new_block);
			}

			construct_at_pack(end(), PP_FORWARD(args)...);

			++count_;
		}

		constexpr T pop_back()
		{
			if (count_ == 0)
				throw 0;

			--count_;

			auto& back = *end();

			auto temp = PP::move(back);

			back.~T();

			return PP::move(temp);
		}

		constexpr void clear() noexcept
		{
			destroy_all();
			block = block.spawn_new(default_capacity);
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
			return block.count();
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
	};
}
