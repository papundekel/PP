#pragma once
#include "type_t.hpp"

namespace PP
{
	namespace detail
	{
		struct get_type__no_type_member_error {};

		template <typename T>
		using get_type_unsafe = typename T::type;

		template <typename T>
		requires requires
		{
			typename T::type;
		}
		constexpr type_t<get_type_unsafe<T>> get_type_helper() noexcept;

		template <typename T>
		constexpr type_t<get_type__no_type_member_error> get_type_helper() noexcept;
	}

	template <typename T>
	using get_type = detail::get_type_unsafe<decltype(detail::get_type_helper<T>())>;
}
