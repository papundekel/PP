#pragma once
#include <cstddef>
#include <type_traits>
#include <memory>
#include <utility>

namespace Papo
{
	template <typename T, std::size_t capacity_, bool looping = false>
	class array_vector
	{
		std::byte buffer[capacity_ * sizeof(T)];
		std::size_t count_;

		constexpr T* begin_helper() noexcept
		{
			return reinterpret_cast<T*>(&buffer);
		}
		constexpr T* end_helper() noexcept
		{
			return begin_helper() + count_;
		}

		constexpr void destroy_all() noexcept
		{
			std::destroy(begin(), end());
		}

	public:
		array_vector()
			= default;
		constexpr array_vector(const array_vector& other) noexcept(std::is_nothrow_copy_constructible_v<T>)
		{
			std::uninitialized_copy(other.begin(), other.end(), begin());
		}
		constexpr array_vector(array_vector&& other) noexcept(std::is_nothrow_move_constructible_v<T>)
		{
			std::uninitialized_move(other.begin(), other.end(), begin());
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
			return count_ == 0;
		}

		constexpr auto count() const noexcept
		{
			return count_;
		}

		constexpr void clear() noexcept
		{
			destroy_all();
			count_ = 0;
		}

		template <typename U>
		constexpr void push_back(U&& object) noexcept(std::is_nothrow_constructible_v<T, U>)
		{
			if (count_ == capacity_)
			{
				if constexpr (!looping)
					std::terminate();
				else
					clear();
			}

			std::construct_at(end(), std::forward<U>(object));
			++count_;
		}

		constexpr void pop_back() noexcept
		{
			if (count_ != 0)
			{
				--count_;
				std::destroy_at(end());
			}
			else
			{
				if constexpr (!looping)
					std::terminate();
			}
		}
	};
}
