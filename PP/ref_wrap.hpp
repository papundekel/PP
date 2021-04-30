#pragma once
#include "add_reference.hpp"
#include "apply_transform.hpp"
#include "concepts/reference.hpp"
#include "conditional.hpp"
#include "decompose_template.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, bool lvalue>
		class ref_wrap_impl
		{
			using RT =
				apply_transform_t<add_reference *
									  value<lvalue ? ref_qualifier::lvalue
												   : ref_qualifier::rvalue>,
								  T>;

			RT ref;

		public:
			constexpr ref_wrap_impl(RT ref) noexcept
				: ref((RT)ref)
			{}

			constexpr RT get() const noexcept
			{
				return (RT)ref;
			}
			constexpr operator RT() const noexcept
			{
				return get();
			}

			constexpr decltype(auto) operator()(auto&&... args) const noexcept
			{
				return get()(PP_FORWARD(args)...);
			}

			static constexpr bool ref_wrap_impl_tag = true;
		};
		template <typename T>
		ref_wrap_impl(T&) -> ref_wrap_impl<T, true>;
		template <typename T>
		ref_wrap_impl(T&&) -> ref_wrap_impl<T, false>;
	}

	template <typename T>
	using ref_wrap = detail::ref_wrap_impl<PP_GET_TYPE(!type<T>),
										   is_lvalue_reference(type<T>)>;

	template <typename T>
	using wrap_ref_t = PP_GET_TYPE(conditional(value<is_reference(type<T>)>,
											   type<ref_wrap<T>>,
											   type<T>));

	PP_FUNCTOR(unwrap_ref, auto&& x) -> auto&&
	{
		if constexpr (requires
					  {
						  x.ref_wrap_impl_tag;
					  })
			return x.get();
		else
			return PP_FORWARD(x);
	});

	constexpr inline auto wrap_ref =
		functor(
			[](auto&& x)
			{
				return ref_wrap<decltype(x)>(PP_FORWARD(x));
			}) |
		unwrap_ref;

#define PP_REF_WRAP(x) ::PP::wrap_ref(PP_FORWARD(x))
}
