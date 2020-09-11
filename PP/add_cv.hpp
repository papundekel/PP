#pragma once
#include "cv_qualifier.hpp"
#include "get_type.hpp"

namespace PP
{
	namespace detail
	{
		template <cv_qualifier cv, typename T>
		constexpr auto add_cv_helper() noexcept
		{
			if constexpr (cv == cv_qualifier::none)
				return type_t<T>{};
			else if constexpr (cv == cv_qualifier::Const)
				return type_t<const T>{};
			else if constexpr (cv == cv_qualifier::Volatile)
				return type_t<volatile T>{};
			else
				return type_t<const volatile T>{};
		}
	}

	template <cv_qualifier cv, typename T>
	using add_cv = get_type<decltype(detail::add_cv_helper<cv, T>())>;
}
