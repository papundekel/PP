#pragma once
#include "function_info.hpp"
#include "overloaded.hpp"
#include "tuple_apply.hpp"
#include "tuple_concept.hpp"
#include "type_tuple.hpp"

namespace PP
{
	namespace detail
	{
		template <typename... Parameters>
		constexpr auto make_function_type_helper(
			concepts::type auto return_type,
			type_tuple_t<Parameters...>,
			concepts::value auto N,
			concepts::value auto C,
			concepts::value auto R)
		{
			using Return = PP_GET_TYPE(return_type);

			constexpr bool Noexcept = PP_GET_VALUE(N);
			constexpr cv_qualifier cv = PP_GET_VALUE(C);
			constexpr ref_qualifier ref = PP_GET_VALUE(R);

			if constexpr (!Noexcept)
			{
				if constexpr (ref == ref_qualifier::none)
				{
					if constexpr (cv == cv_qualifier::none)
						return type<Return(Parameters...)>;
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
						return type<Return(Parameters...)&>;
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
						return type<Return(Parameters...)
										const volatile noexcept>;
				}
				else if constexpr (ref == ref_qualifier::lvalue)
				{
					if constexpr (cv == cv_qualifier::none)
						return type<Return(Parameters...)& noexcept>;
					else if constexpr (cv == cv_qualifier::Const)
						return type<Return(Parameters...) const& noexcept>;
					else if constexpr (cv == cv_qualifier::Volatile)
						return type<Return(Parameters...) volatile& noexcept>;
					else
						return type<Return(Parameters...)
										const volatile& noexcept>;
				}
				else
				{
					if constexpr (cv == cv_qualifier::none)
						return type<Return(Parameters...)&& noexcept>;
					else if constexpr (cv == cv_qualifier::Const)
						return type<Return(Parameters...) const&& noexcept>;
					else if constexpr (cv == cv_qualifier::Volatile)
						return type<Return(Parameters...) volatile&& noexcept>;
					else
						return type<Return(Parameters...)
										const volatile&& noexcept>;
				}
			}
		}

		PP_FUNCTOR(make_function_type_impl,
				   concepts::type auto return_type,
				   concepts::tuple auto parameter_types,
				   concepts::value auto Noexcept,
				   concepts::value auto cv,
				   concepts::value auto ref)
		{
			return make_function_type_helper(return_type,
											 make_type_tuple[parameter_types],
											 Noexcept,
											 cv,
											 ref);
		});

		PP_FUNCTOR(make_function_type_from_type,
				   concepts::type auto t,
				   concepts::value auto Noexcept,
				   concepts::value auto cv,
				   concepts::value auto ref)
		{
			auto info = get_function_info(t);
			return make_function_type_impl(info.return_type,
										   info.parameter_types,
										   Noexcept,
										   cv,
										   ref);
		});

		PP_FUNCTOR(make_function_type_from_type_nocvref,
				   concepts::type auto t,
				   concepts::value auto Noexcept)
		{
			return make_function_type_from_type(t,
												Noexcept,
												value<cv_qualifier::none>,
												value<ref_qualifier::none>);
		});
	}

	constexpr inline auto make_function_type = make_overloaded_pack(
		detail::make_function_type_impl,
		detail::make_function_type_from_type,
		detail::make_function_type_from_type_nocvref,
		[](concepts::value auto info)
		{
			constexpr auto INFO = PP_COPY_VALUE(info);

			return detail::make_function_type_impl(INFO.return_type,
												   INFO.parameter_types,
												   value<INFO.Noexcept>,
												   value<INFO.cv>,
												   value<INFO.ref>);
		});
}
