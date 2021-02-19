#pragma once
#include "unique_pointer.hpp"
#include "pointer_allocate.hpp"
#include "view.hpp"
#include "view_copy_uninitialized.hpp"

namespace PP
{
	template <typename T, typename Allocator>
	class dynamic_block
	{
		unique_pointer<pointer_allocate<T, Allocator>> buffer;

		constexpr T* begin_helper() const noexcept
		{
			return buffer.get();
		}
		constexpr T* end_helper() const noexcept
		{
			return begin_helper() + count();
		}

	public:
		constexpr dynamic_block(auto&& allocator, size_t count) noexcept
			: buffer(placeholder, PP_FORWARD(allocator), count)
		{}
		constexpr dynamic_block(auto&& allocator, concepts::view auto&& v)
			: dynamic_block(PP_FORWARD(allocator), view_count(PP_FORWARD(v)))
		{
			view_copy_uninitialized(*this, PP_FORWARD(v));
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

		constexpr size_t count() const noexcept
		{
			return buffer.get_object().count();
		}
	};
}
