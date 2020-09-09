#pragma once
#include "cv_qualifier.hpp"
#include "ref_qualifier.hpp"
#include "get_function_info.hpp"
#include "apply_pack.hpp"
#include "get_value_type.hpp"

namespace PP
{
	namespace detail
	{
		template <cv_qualifier cv, ref_qualifier ref, bool Noexcept, typename Return>
		struct add_function_cvrefn_helper
		{
			template <typename... Args>
			struct help
			{
				static constexpr auto value_f() noexcept
				{
					if constexpr (!Noexcept)
					{
						if constexpr (ref == ref_qualifier::none)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Args...)>{};
							else if constexpr (cv == cv_qualifier::const_)
								return type_t<Return(Args...) const>{};
							else if constexpr (cv == cv_qualifier::volatile_)
								return type_t<Return(Args...) volatile>{};
							else
								return type_t<Return(Args...) const volatile>{};
						}
						else if constexpr (ref == ref_qualifier::lvalue)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Args...)&>{};
							else if constexpr (cv == cv_qualifier::const_)
								return type_t<Return(Args...) const&>{};
							else if constexpr (cv == cv_qualifier::volatile_)
								return type_t<Return(Args...) volatile&>{};
							else
								return type_t<Return(Args...) const volatile&>{};
						}
						else
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Args...)&&>{};
							else if constexpr (cv == cv_qualifier::const_)
								return type_t<Return(Args...) const&&>{};
							else if constexpr (cv == cv_qualifier::volatile_)
								return type_t<Return(Args...) volatile&&>{};
							else
								return type_t<Return(Args...) const volatile&&>{};
						}
					}
					else
					{
						if constexpr (ref == ref_qualifier::none)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Args...) noexcept>{};
							else if constexpr (cv == cv_qualifier::const_)
								return type_t<Return(Args...) const noexcept>{};
							else if constexpr (cv == cv_qualifier::volatile_)
								return type_t<Return(Args...) volatile noexcept>{};
							else
								return type_t<Return(Args...) const volatile noexcept>{};
						}
						else if constexpr (ref == ref_qualifier::lvalue)
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Args...) & noexcept>{};
							else if constexpr (cv == cv_qualifier::const_)
								return type_t<Return(Args...) const& noexcept>{};
							else if constexpr (cv == cv_qualifier::volatile_)
								return type_t<Return(Args...) volatile& noexcept>{};
							else
								return type_t<Return(Args...) const volatile& noexcept>{};
						}
						else
						{
							if constexpr (cv == cv_qualifier::none)
								return type_t<Return(Args...) && noexcept>{};
							else if constexpr (cv == cv_qualifier::const_)
								return type_t<Return(Args...) const&& noexcept>{};
							else if constexpr (cv == cv_qualifier::volatile_)
								return type_t<Return(Args...) volatile&& noexcept>{};
							else
								return type_t<Return(Args...) const volatile&& noexcept>{};
						}
					}
				}
			};
		};
	}

	template <cv_qualifier cv, ref_qualifier ref, bool Noexcept, typename F>
	using add_function_cvrefn =
		get_value_type
		<
			apply_pack
			<
				detail::add_function_cvrefn_helper
				<
					cv,
					ref,
					Noexcept,
					typename get_function_info<F>::return_type
				>::template help,
				typename get_function_info<F>::parameter_types
			>
		>;
}
