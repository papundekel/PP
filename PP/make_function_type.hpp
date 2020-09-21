#pragma once
#include "overloaded.hpp"
#include "function_info.hpp"

namespace PP
{
	namespace detail
	{
		struct make_function_type_helper
		{
			template <cv_qualifier cv = cv_qualifier::none, ref_qualifier ref = ref_qualifier::none, bool Noexcept = false, typename Return, typename... Parameters >
			constexpr auto operator()
				( type_t<Return>
				, type_tuple<Parameters...>
				, value_t<Noexcept> = {}
				, value_t<cv> = {}
				, value_t<ref> = {}) const noexcept
			{
				if constexpr (!Noexcept)
				{
					if constexpr (ref == ref_qualifier::none)
					{
						if constexpr (cv == cv_qualifier::none)
							return type_v<Return(Parameters...)>;
						else if constexpr (cv == cv_qualifier::Const)
							return type_v<Return(Parameters...) const>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type_v<Return(Parameters...) volatile>;
						else
							return type_v<Return(Parameters...) const volatile>;
					}
					else if constexpr (ref == ref_qualifier::lvalue)
					{
						if constexpr (cv == cv_qualifier::none)
							return type_v<Return(Parameters...)&>;
						else if constexpr (cv == cv_qualifier::Const)
							return type_v<Return(Parameters...) const&>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type_v<Return(Parameters...) volatile&>;
						else
							return type_v<Return(Parameters...) const volatile&>;
					}
					else
					{
						if constexpr (cv == cv_qualifier::none)
							return type_v<Return(Parameters...)&&>;
						else if constexpr (cv == cv_qualifier::Const)
							return type_v<Return(Parameters...) const&&>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type_v<Return(Parameters...) volatile&&>;
						else
							return type_v<Return(Parameters...) const volatile&&>;
					}
				}
				else
				{
					if constexpr (ref == ref_qualifier::none)
					{
						if constexpr (cv == cv_qualifier::none)
							return type_v<Return(Parameters...) noexcept>;
						else if constexpr (cv == cv_qualifier::Const)
							return type_v<Return(Parameters...) const noexcept>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type_v<Return(Parameters...) volatile noexcept>;
						else
							return type_v<Return(Parameters...) const volatile noexcept>;
					}
					else if constexpr (ref == ref_qualifier::lvalue)
					{
						if constexpr (cv == cv_qualifier::none)
							return type_v<Return(Parameters...) & noexcept>;
						else if constexpr (cv == cv_qualifier::Const)
							return type_v<Return(Parameters...) const& noexcept>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type_v<Return(Parameters...) volatile& noexcept>;
						else
							return type_v<Return(Parameters...) const volatile& noexcept>;
					}
					else
					{
						if constexpr (cv == cv_qualifier::none)
							return type_v<Return(Parameters...) && noexcept>;
						else if constexpr (cv == cv_qualifier::Const)
							return type_v<Return(Parameters...) const&& noexcept>;
						else if constexpr (cv == cv_qualifier::Volatile)
							return type_v<Return(Parameters...) volatile&& noexcept>;
						else
							return type_v<Return(Parameters...) const volatile&& noexcept>;
					}
				}
			}
		};
	}
	
	constexpr inline auto make_function_type = overloaded{ detail::make_function_type_helper{},
		[]<function_info info>(value_t<info>) { return detail::make_function_type_helper{}(info.return_type, info.parameter_types, value_v<info.Noexcept>, value_v<info.cv>, value_v<info.ref>); } };
}
