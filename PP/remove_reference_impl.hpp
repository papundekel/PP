#pragma once
#include "declval_impl.hpp"
#include "type_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		type_t<T> remove_reference_impl_helper(T&);
		template <typename T>
		type_t<T> remove_reference_impl_helper(T&&);
	}

	template <typename T>
	using remove_reference_impl =
		decltype(detail::remove_reference_impl_helper(declval_impl<T>()))::type;
}
