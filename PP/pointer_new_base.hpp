#pragma once
#include "concepts/convertible_to.hpp"
#include "exchange.hpp"
#include "unique.hpp"

namespace PP
{
	namespace detail
	{
		template <typename U, typename T>
		concept pointer_new_compatible = concepts::convertible_to<U*, T*>;
	}

	template <typename T>
	class pointer_new_base
	{
		template <typename>
		friend class pointer_new_base;

		template <typename>
		friend class pointer_new;
		template <typename>
		friend class pointer_new_array;
		template <typename, typename>
		friend class pointer_allocate;

		T* ptr;

	public:
		explicit constexpr pointer_new_base(T* ptr) noexcept
			: ptr(ptr)
		{}

		constexpr pointer_new_base() noexcept
			: ptr(nullptr)
		{}

		template <detail::pointer_new_compatible<T> U>
		constexpr pointer_new_base(pointer_new_base<U>&& other) noexcept
			: ptr(PP::exchange(other.ptr, nullptr))
		{}

		constexpr pointer_new_base& operator=(pointer_new_base&& other) noexcept
		{
			ptr = PP::exchange(other.ptr, nullptr);
			return *this;
		}
		template <detail::pointer_new_compatible<T> U>
		constexpr pointer_new_base& operator=(
			pointer_new_base<U>&& other) noexcept
		{
			ptr = PP::exchange(other.ptr, nullptr);
			return *this;
		}

		constexpr T* get_ptr() const noexcept
		{
			return ptr;
		}
	};
}
