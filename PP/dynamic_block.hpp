#pragma once
#include "uninitialized_copy.hpp"
#include "unique_pointer.hpp"
#include "view.hpp"

namespace PP
{
	template <typename T>
	class dynamic_block
	{
		size_t count_;
		unique_pointer<pointer_new_array<std::byte>> buffer;

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
			, buffer(pointer_new_array<std::byte>(count_))
		{}
		explicit constexpr dynamic_block(concepts::view auto&& v)
			: dynamic_block(PP::view_count(PP_FORWARD(v)))
		{
			uninitialized_copy(*this, PP_FORWARD(v));
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

		constexpr std::size_t count() const noexcept
		{
			return count_;
		}
	};
}
