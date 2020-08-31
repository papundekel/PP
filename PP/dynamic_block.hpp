#pragma once
#include <memory>
#include <cstddef>
#include "unique_pointer.hpp"

namespace PP
{
	template <typename T>
	class dynamic_block
	{
		std::size_t count_;
		unique_pointer<std::byte[]> buffer;

		constexpr T* begin_helper() const noexcept
		{
			return reinterpret_cast<T*>(buffer.get());
		}
		constexpr T* end_helper() const noexcept
		{
			return begin_helper() + count_;
		}

	public:
		explicit constexpr dynamic_block(std::size_t count) noexcept
			: count_(count)
			, buffer(new std::byte[count_ * sizeof(T)])
		{}

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

		constexpr std::size_t count() const noexcept
		{
			return count_;
		}
	};
}
