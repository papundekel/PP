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
		template <typename, typename>
		friend class pointer_allocate;

		compressed_pair<size_t, Allocator> count_allocator;

	public:
		constexpr pointer_allocate(auto&& allocator, size_t count)
			: pointer_new_base<T>(allocator.allocate(count))
			, count_allocator(count, PP_FORWARD(allocator))
		{}

		template <detail::pointer_new_compatible<T> U, typename AllocatorOther>
		constexpr pointer_allocate(const pointer_allocate<U, AllocatorOther>& other) noexcept
			: pointer_new_base<T>(other)
			, count_allocator(other.count_allocator.first, other.count_allocator.second)
		{}
		template <detail::pointer_new_compatible<T> U, typename AllocatorOther>
		constexpr pointer_allocate(pointer_allocate<U, AllocatorOther>&& other) noexcept
			: pointer_new_base<T>(move(other))
			, count_allocator(other.count_allocator.first, move(other).count_allocator.second)
		{}

		template <detail::pointer_new_compatible<T> U, typename AllocatorOther>
		constexpr pointer_allocate& operator=(pointer_allocate<U, AllocatorOther>&& other) noexcept
		{
			pointer_new_base<T>::operator=(move(other));
			return *this;
		}

		constexpr size_t count() const
		{
			return count_allocator.first;
		}

		constexpr void deallocate()
		{
			if (this->ptr)
				count_allocator.second.deallocate(this->ptr, count());
		}

		constexpr auto& get_allocator()
		{
			return count_allocator.second;
		}
	};
}
