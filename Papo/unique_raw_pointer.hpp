#pragma once
#include <utility>

namespace Papo
{
	template <typename T>
	class unique_raw_pointer
	{
		T* ptr;

	public:
		constexpr unique_raw_pointer(T* ptr) noexcept
			: ptr(ptr)
		{}
		constexpr unique_raw_pointer(unique_raw_pointer&& other) noexcept
			: ptr(std::exchange(other.ptr, nullptr))
		{}
		constexpr unique_raw_pointer& operator=(unique_raw_pointer&& other) noexcept
		{
			ptr = std::exchange(other.ptr, nullptr);
			return *this;
		}
		constexpr T* get() const noexcept
		{
			return ptr;
		}
	};
}
