#pragma once
#include "pointer_allocate.hpp"
#include "unique_pointer.hpp"
#include "view.hpp"
#include "view_copy_uninitialized.hpp"

namespace PP
{
	template <typename T, typename Allocator>
	class dynamic_block
	{
		template <typename, typename>
		friend class dynamic_block;

		unique_pointer<pointer_allocate<T, Allocator>> ptr;

		constexpr T* begin_helper() const noexcept
		{
			return ptr.get();
		}
		constexpr T* end_helper() const noexcept
		{
			return begin_helper() + count();
		}

	public:
		constexpr dynamic_block(auto&& allocator, size_t count) noexcept
			: ptr(placeholder, PP_FORWARD(allocator), count)
		{}
		constexpr dynamic_block(auto&& allocator, concepts::view auto&& v)
			: dynamic_block(PP_FORWARD(allocator), view_count(PP_FORWARD(v)))
		{
			view_copy_uninitialized(*this, PP_FORWARD(v));
		}

		template <typename AllocatorOther>
		constexpr dynamic_block(dynamic_block<T, AllocatorOther>&& other)
			: ptr(move(other).ptr)
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

		constexpr size_t count() const noexcept
		{
			return ptr.get_object().count();
		}

		constexpr auto spawn_new(size_t count)
		{
			return dynamic_block<T, Allocator&>(
				ptr.get_object().get_allocator(),
				count);
		}
	};
}
