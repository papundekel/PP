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
class pointer_base
{
	template <typename>
	friend class pointer_base;

	template <typename>
	friend class pointer_new;
	template <typename>
	friend class pointer_new_array;
	template <typename, typename>
	friend class pointer_allocate;

	T* ptr;

public:
	explicit constexpr pointer_base(T* ptr) noexcept
		: ptr(ptr)
	{}

	constexpr pointer_base() noexcept
		: ptr(nullptr)
	{}
	constexpr pointer_base(decltype(nullptr)) noexcept
		: pointer_base()
	{}

	pointer_base(const pointer_base& other) = default;

	template <detail::pointer_new_compatible<T> U>
	constexpr pointer_base(const pointer_base<U>& other) noexcept
		: ptr(other.ptr)
	{}

	pointer_base& operator=(const pointer_base& other) = default;

	template <detail::pointer_new_compatible<T> U>
	constexpr pointer_base& operator=(const pointer_base<U>& other) noexcept
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
