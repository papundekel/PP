#pragma once
#include "type_t.hpp"
#include "cv_qualifier.hpp"
#include "ref_qualifier.hpp"
#include "get_value_type.hpp"
#include "apply_pack.hpp"

namespace PP
{
	namespace detail
	{
		template <typename Return, bool Noexcept, cv_qualifier cv, ref_qualifier ref>
		struct make_function_type
		{
			template <typename... Parameters>
			struct help
			{
				static constexpr auto value_f() noexcept
				{
					if constexpr (!Noexcept)
					{
						if constexpr (ref == ref_qualifier::none)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Parameters...)>{};
							else if constexpr (cv == cv_qualifier::Const)
								return type_t<Return(Parameters...) const>{};
							else if constexpr (cv == cv_qualifier::Volatile)
								return type_t<Return(Parameters...) volatile>{};
							else
								return type_t<Return(Parameters...) const volatile>{};
						}
						else if constexpr (ref == ref_qualifier::lvalue)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Parameters...)&>{};
							else if constexpr (cv == cv_qualifier::Const)
								return type_t<Return(Parameters...) const&>{};
							else if constexpr (cv == cv_qualifier::Volatile)
								return type_t<Return(Parameters...) volatile&>{};
							else
								return type_t<Return(Parameters...) const volatile&>{};
						}
						else
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Parameters...)&&>{};
							else if constexpr (cv == cv_qualifier::Const)
								return type_t<Return(Parameters...) const&&>{};
							else if constexpr (cv == cv_qualifier::Volatile)
								return type_t<Return(Parameters...) volatile&&>{};
							else
								return type_t<Return(Parameters...) const volatile&&>{};
						}
					}
					else
					{
						if constexpr (ref == ref_qualifier::none)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Parameters...) noexcept>{};
							else if constexpr (cv == cv_qualifier::Const)
								return type_t<Return(Parameters...) const noexcept>{};
							else if constexpr (cv == cv_qualifier::Volatile)
								return type_t<Return(Parameters...) volatile noexcept>{};
							else
								return type_t<Return(Parameters...) const volatile noexcept>{};
						}
						else if constexpr (ref == ref_qualifier::lvalue)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Parameters...) & noexcept>{};
							else if constexpr (cv == cv_qualifier::Const)
								return type_t<Return(Parameters...) const& noexcept>{};
							else if constexpr (cv == cv_qualifier::Volatile)
								return type_t<Return(Parameters...) volatile& noexcept>{};
							else
								return type_t<Return(Parameters...) const volatile& noexcept>{};
						}
						else
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Parameters...) && noexcept>{};
							else if constexpr (cv == cv_qualifier::Const)
								return type_t<Return(Parameters...) const&& noexcept>{};
							else if constexpr (cv == cv_qualifier::Volatile)
								return type_t<Return(Parameters...) volatile&& noexcept>{};
							else
								return type_t<Return(Parameters...) const volatile&& noexcept>{};
						}
					}
				}
			};
		};
	}

	template <typename Return, typename Parameters, bool Noexcept, cv_qualifier cv = cv_qualifier::none, ref_qualifier ref = ref_qualifier::none>
	using make_function_type = get_type<get_value_type<apply_pack<detail::make_function_type<Return, Noexcept, cv, ref>::template help, Parameters>>>;
}
