#pragma once
#include "get_type.hpp"
#include "placeholder.hpp"
#include "pointer_new_base.hpp"

namespace PP
{
	template <typename T>
	class pointer_new : public pointer_new_base<T>
	{
	public:
		using pointer_new_base<T>::pointer_new_base;

		constexpr pointer_new(
			const pointer_new<detail::pointer_new_compatible<T> auto>&
				other) noexcept
			: pointer_new_base<T>(other.ptr)
		{}

	private:
		constexpr pointer_new(placeholder_t, auto&&... args)
			: pointer_new_base<T>(new T(PP_FORWARD(args)...))
		{}

	public:
		static constexpr auto create(auto&&... args)
		{
			return pointer_new(placeholder, PP_FORWARD(args)...);
		}

		constexpr void deallocate()
		{
			delete this->ptr;
		}
	};
}
