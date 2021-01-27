#pragma once
#include "overloaded.hpp"
#include "function_info.hpp"

namespace PP
{
	namespace detail
	{
		constexpr inline auto make_function_type_helper = []
			<cv_qualifier cv = cv_qualifier::none, ref_qualifier ref = ref_qualifier::none, bool Noexcept = false, typename Return, typename... Parameters >
				( type_t<Return>
				, type_tuple<Parameters...>
				, value_t<Noexcept> = {}
				, value_t<cv> = {}
				, value_t<ref> = {})
			{
				if constexpr (!Noexcept)
				{
					if constexpr (ref == ref_qualifier::none)
					{
						if constexpr (cv == cv_qualifier::none)
							return type<Return(Parameters...) >;
						else if constexpr (cv == cv_qualifier::Const)
							return type<Return(Parameters...) const>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type<Return(Parameters...) volatile>;
						else
							return type<Return(Parameters...) const volatile>;
					}
					else if constexpr (ref == ref_qualifier::lvalue)
					{
						if constexpr (cv == cv_qualifier::none)
							return type<Return(Parameters...) &>;
						else if constexpr (cv == cv_qualifier::Const)
							return type<Return(Parameters...) const&>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type<Return(Parameters...) volatile&>;
						else
							return type<Return(Parameters...) const volatile&>;
					}
					else
					{
						if constexpr (cv == cv_qualifier::none)
							return type<Return(Parameters...) &&>;
						else if constexpr (cv == cv_qualifier::Const)
							return type<Return(Parameters...) const&&>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type<Return(Parameters...) volatile&&>;
						else
							return type<Return(Parameters...) const volatile&&>;
					}
				}
				else
				{
					if constexpr (ref == ref_qualifier::none)
					{
						if constexpr (cv == cv_qualifier::none)
							return type<Return(Parameters...) noexcept>;
						else if constexpr (cv == cv_qualifier::Const)
							return type<Return(Parameters...) const noexcept>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type<Return(Parameters...) volatile noexcept>;
						else
							return type<Return(Parameters...) const volatile noexcept>;
					}
					else if constexpr (ref == ref_qualifier::lvalue)
					{
						if constexpr (cv == cv_qualifier::none)
							return type<Return(Parameters...) & noexcept>;
						else if constexpr (cv == cv_qualifier::Const)
							return type<Return(Parameters...) const& noexcept>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type<Return(Parameters...) volatile& noexcept>;
						else
							return type<Return(Parameters...) const volatile& noexcept>;
					}
					else
					{
						if constexpr (cv == cv_qualifier::none)
							return type<Return(Parameters...) && noexcept>;
						else if constexpr (cv == cv_qualifier::Const)
							return type<Return(Parameters...) const&& noexcept>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type<Return(Parameters...) volatile&& noexcept>;
						else
							return type<Return(Parameters...) const volatile&& noexcept>;
					}
				}
			};
	}
	
	constexpr inline auto make_function_type = overloaded{
		detail::make_function_type_helper,
		[]<auto info>(value_t<info>)
		{
			return detail::make_function_type_helper(info.return_type, info.parameter_types, value<info.Noexcept>, value<info.cv>, value<info.ref>);
		} };
}
