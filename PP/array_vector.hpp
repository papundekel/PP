#pragma once
#include <exception>

#include "construct_at_pack.hpp"
#include "destroy_at.hpp"
#include "view_destroy.hpp"
#include "zero_initialized.hpp"

namespace PP
{
	template <typename T, size_t capacity_, bool looping = false>
	class array_vector
	{
		char buffer[capacity_ * sizeof(T)];
		zero_initialized<size_t> count_;

		constexpr T* begin_helper() noexcept
		{
			return reinterpret_cast<T*>(&buffer);
		}
		constexpr T* end_helper() noexcept
		{
			return begin_helper() + count();
		}

		constexpr void destroy_all() noexcept
		{
			view_destroy(*this);
		}

	public:
		array_vector() = default;

		constexpr array_vector(const array_vector& other)
		{
			view_copy_uninitialized(*this, other);
		}
		constexpr array_vector(array_vector&& other)
		{
			view_move_uninitialized(*this, other);
		}
		constexpr ~array_vector()
		{
			destroy_all();
		}

		constexpr T* begin() noexcept
		{
			return begin_helper();
		}
		constexpr const T* begin() const noexcept
		{
			return begin_helper();
		}
		constexpr T* end() noexcept
		{
			return end_helper();
		}
		constexpr const T* end() const noexcept
		{
			return end_helper();
		}

		constexpr bool empty() const noexcept
		{
			return count() == 0;
		}

		constexpr auto count() const noexcept
		{
			return count_.value;
		}

		constexpr void clear() noexcept
		{
			destroy_all();
			count_.value = 0;
		}

		constexpr void push_back(auto&& object)
		{
			if (count() == capacity_)
			{
				if constexpr (!looping)
					std::terminate();
				else
					clear();
			}

			construct_at_pack(end(), PP_FORWARD(object));
			++count_.value;
		}

		constexpr void pop_back() noexcept
		{
			if (!empty())
			{
				--count_.value;
				destroy_at(end());
			}
			else
			{
				if constexpr (!looping)
					std::terminate();
			}
		}
	};
}
