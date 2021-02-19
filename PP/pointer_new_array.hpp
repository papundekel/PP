#pragma once
#include "get_type.hpp"
#include "pointer_new_base.hpp"
#include "size_t.hpp"

namespace PP
{
	template <typename T>
	class pointer_new_array : public pointer_new_base<T>
	{
	public:
		using pointer_new_base<T>::pointer_new_base;

		constexpr pointer_new_array(size_t count)
			: pointer_new_base<T>(new T[count])
		{}

		constexpr pointer_new_array(const pointer_new_array<detail::pointer_new_compatible<T> auto>& other) noexcept
			: pointer_new_base<T>(other.ptr)
		{}

		constexpr void destroy()
		{
			delete[] this->ptr;
		}
	};
}
