#pragma once
#include "concepts/convertible_to.hpp"
#include "exchange.hpp"
#include "movable.hpp"
#include "tags.hpp"

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
		constexpr pointer_new_base(decltype(nullptr)) noexcept
			: pointer_new_base()
		{}

		pointer_new_base(const pointer_new_base& other) = default;

		template <detail::pointer_new_compatible<T> U>
		constexpr pointer_new_base(const pointer_new_base<U>& other) noexcept
			: ptr(other.ptr)
		{}

		pointer_new_base& operator=(const pointer_new_base& other) = default;

		template <detail::pointer_new_compatible<T> U>
		constexpr pointer_new_base& operator=(
			const pointer_new_base<U>& other) noexcept
		{
			ptr = other.ptr;
			return *this;
		}

		constexpr auto get_ptr() const noexcept
		{
			return ptr;
		}
		constexpr auto operator[](tags::p_t) const noexcept
		{
			return get_ptr();
		}
	};
}
