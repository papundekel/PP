#pragma once
#include <memory>
#include <type_traits>

#include "size_t.hpp"

namespace PP
{
	template <typename T, size_t Count>
	class static_block
	{
		union
		{
			alignas(T) char buffer[Count * sizeof(T)];
			T* constexpr_ptr;
		};
		bool constant_created;

	public:
		constexpr static_block() noexcept
			: buffer()
			, constant_created(false)
		{
			if (std::is_constant_evaluated())
			{
				constexpr_ptr = std::allocator<T>().allocate(Count);
				constant_created = true;
			}
		}

		constexpr ~static_block() noexcept
		{
			if (constant_created)
				std::allocator<T>().deallocate(constexpr_ptr, Count);
		}

		constexpr T* begin() noexcept
		{
			if (constant_created)
				return constexpr_ptr;
			else
				return reinterpret_cast<T*>(buffer);
		}

		constexpr const T* begin() const noexcept
		{
			if (constant_created)
				return constexpr_ptr;
			else
				return reinterpret_cast<const T*>(buffer);
		}

		constexpr T* end() noexcept
		{
			return begin() + count();
		}

		constexpr const T* end() const noexcept
		{
			return begin() + count();
		}

		constexpr auto count() const noexcept
		{
			return Count;
		}
	};
}
