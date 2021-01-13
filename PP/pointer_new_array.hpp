#pragma once
#include <cstddef>
#include <type_traits>
#include "pointer_new_base.hpp"

namespace PP
{
	template <typename T>
	class pointer_new_array : public pointer_new_base<T>
	{
	public:
		using pointer_new_base<T>::pointer_new_base;

		template <typename... Args>
		constexpr pointer_new_array(PP::type_t<T>, std::size_t count) // TODO noexcept(?)
			: pointer_new_base<T>(new T[count])
		{}

		constexpr pointer_new_array(const pointer_new_array<pointer_new_compatible<T> auto>& other) noexcept
		{
			this->ptr = other.ptr;
		}

		constexpr void destroy() const
		{
			delete[] this->ptr;
		}
	};
}
