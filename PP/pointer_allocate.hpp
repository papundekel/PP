#pragma once
#include "compressed_pair.hpp"
#include "get_type.hpp"
#include "pointer_new_base.hpp"
#include "size_t.hpp"

namespace PP
{
	template <typename T, typename Allocator>
	class pointer_allocate : public pointer_new_base<T>
	{
		compressed_pair<size_t, Allocator> count_allocator;

	public:
		using pointer_new_base<T>::pointer_new_base;

		constexpr pointer_allocate(auto&& allocator, size_t count)
			: pointer_new_base<T>(allocator.allocate(count))
			, count_allocator(count, PP_FORWARD(allocator))
		{}

		constexpr pointer_allocate(const pointer_allocate<detail::pointer_new_compatible<T> auto, auto>& other) noexcept
			: pointer_new_base<T>(other.ptr)
			, count_allocator(other.count_allocator)
		{}

		constexpr size_t count() const
		{
			return count_allocator.first;
		}

		constexpr void destroy()
		{
			count_allocator.second.deallocate(this->get_ptr(), count());
		}
	};
}
