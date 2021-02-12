#pragma once
#include "concepts/convertible_to.hpp"

namespace PP
{
	template <typename U, typename T>
	concept pointer_new_compatible = concepts::convertible_to<U*, T*>;
	
	template <typename T>
	class pointer_new_base
	{
		template <typename U>
		friend class pointer_new;
		template <typename U>
		friend class pointer_new_array;

		T* ptr;

	public:
		constexpr pointer_new_base(T* ptr) noexcept
			: ptr(ptr)
		{}

		constexpr pointer_new_base() noexcept
			: ptr(nullptr)
		{}

		constexpr T* get_ptr() const noexcept
		{
			return ptr;
		}
	};
}
