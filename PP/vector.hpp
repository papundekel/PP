#pragma once
#include "construct_at_pack.hpp"
#include "dynamic_block.hpp"
#include "movable.hpp"
#include "no_default_initialized.hpp"
#include "view/concept.hpp"
#include "view/destroy.hpp"
#include "view/move_uninitialized.hpp"
#include "view/remove.hpp"

namespace std
{
template <typename T>
struct allocator;
}

namespace PP
{
template <typename T, typename Allocator = std::allocator<T>>
class vector
{
	static constexpr size_t default_capacity = 16;

	dynamic_block<T, Allocator> block;
	movable<no_default_initialized<size_t>, zero_releaser> count_;

	constexpr void destroy_all() noexcept
	{
		view_destroy(*this);
	}

public:
	constexpr vector(auto&& allocator, size_t capacity) noexcept
	    : block(PP_F(allocator), capacity)
	    , count_(movable_default_releaser_tag, 0)
	{}
	constexpr vector(auto&& allocator, concepts::view auto&& v)
	    : block(PP_F(allocator), PP_F(v))
	    , count_(block.count())
	{}
	explicit constexpr vector(size_t capacity) noexcept
	    : vector(Allocator(), capacity)
	{}
	explicit constexpr vector(concepts::view auto&& v)
	    : vector(Allocator(), PP_F(v))
	{}
	constexpr vector(placeholder_t, auto&& allocator) noexcept
	    : vector(PP_F(allocator), default_capacity)
	{}
	constexpr vector(placeholder_t, size_t count) noexcept
	    : vector(count)
	{
		view_for_each(
		    [](T& t)
		    {
			    construct_at_pack(&t);
		    },
		    *this);
	}
	constexpr vector() noexcept
	    : vector(Allocator(), default_capacity)
	{}

	vector(vector&&) = default;
	vector& operator=(vector&&) = default;

	constexpr ~vector()
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

		construct_at_pack(end(), PP_F(args)...);

		++count_[tags::o];
	}

	constexpr T pop_back()
	{
		if (count() == 0)
			throw 0;

		--count_[tags::o];

		auto& back = *end();

		auto temp = PP::move(back);

		back.~T();

		return PP::move(temp);
	}

	constexpr void clear() noexcept
	{
		destroy_all();
		block = block.spawn_new(default_capacity);
		count_[tags::o] = 0;
	}

	constexpr T* begin() noexcept
	{
		return block.begin();
	}
	constexpr T* end() noexcept
	{
		return begin() + count();
	}
	constexpr const T* begin() const noexcept
	{
		return block.begin();
	}
	constexpr const T* end() const noexcept
	{
		return begin() + count();
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
		return count() == 0;
	}
	constexpr size_t count() const noexcept
	{
		return count_[tags::o];
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
		auto i = view_remove(PP_F(predicate), *this);
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
