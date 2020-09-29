#pragma once
#include "type_t.hpp"
#include "has_type.hpp"
#include "get_value.h"

namespace PP
{
	namespace detail
	{
		struct get_type__no_type_member_error {};

		template <typename T>
		using get_type_unsafe = typename T::type;

		template <typename T>
		concept has_value_any = has_value_f<T> || has_value<T>;

		template <has_type T>
		constexpr type_t<get_type_unsafe<T>> get_type_helper() noexcept;

		template <typename T>
		requires (!has_type<T> && has_value_any<T>)
		constexpr decltype(get_type_helper<decltype(get_value<T>())>()) get_type_helper() noexcept;

		template <typename T>
		constexpr type_t<get_type__no_type_member_error> get_type_helper() noexcept;
	}

	template <typename T>
	using get_type = detail::get_type_unsafe<decltype(detail::get_type_helper<T>())>;
}

#include "get_value.hpp"
