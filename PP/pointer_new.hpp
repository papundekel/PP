#pragma once
#include "type_t.hpp"
#include <type_traits>
#include "pointer_new_base.hpp"
#include "placeholder.hpp"

namespace PP
{
	template <typename T>
	class pointer_new : public pointer_new_base<T>
	{
	public:
		using pointer_new_base<T>::pointer_new_base;

		template <typename... Args>
		constexpr pointer_new(PP::type_t<T>, Args&&... args) // TODO noexcept(?)
			: pointer_new_base<T>(new T(std::forward<Args>(args)...))
		{}

		constexpr pointer_new(placeholder_t, auto&& value)
			: pointer_new(PP::type_v<std::remove_cvref_t<decltype(value)	>>, std::forward<decltype(value)>(value))
		{}

		constexpr pointer_new(const pointer_new<pointer_new_compatible<T> auto>& other) noexcept
		{
			this->ptr = other.ptr;
		}

		constexpr void destroy() const
		{
			delete this->ptr;
		}
	};
}
