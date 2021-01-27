#pragma once
#include "add_reference.hpp"
#include "apply_transform.hpp"
#include "concepts/convertible_to.hpp"
#include "decompose_template.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "remove_reference.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, typename rvalue>
		class reference_wrapper
		{
			using reference_type = PP_GET_TYPE(add_reference(rvalue{}, type<T>));

		public:
			T* ptr;

			template <typename U, typename other_rvalue>
			requires concepts::convertible_to<U*, T*> && (rvalue{} == other_rvalue{})
			constexpr reference_wrapper(reference_wrapper<U, other_rvalue> r) noexcept
				: ptr(r.ptr)
			{}
			constexpr reference_wrapper(reference_type ref) noexcept
				: ptr(&ref)
			{}

			constexpr auto&& get() const noexcept
			{
				return (reference_type)(*ptr);
			}
			constexpr operator reference_type() const noexcept
			{
				return get();
			}

			constexpr decltype(auto) operator()(auto&&... args) const
			requires requires { get()(PP_FORWARD(args)...); }
			{
				return get()(PP_FORWARD(args)...);
			}

			template <typename U, typename other_rvalue>
			requires concepts::convertible_to<U*, T*> && (bool(rvalue{} == other_rvalue{}))
			constexpr auto& operator=(reference_wrapper<U, other_rvalue> other) noexcept
			{
				ptr = other.ptr;
				return *this;
			}
		};
		template <typename T>
		reference_wrapper(T&)->reference_wrapper<T, value_t<false>>;
		template <typename T>
		reference_wrapper(T&&)->reference_wrapper<T, value_t<true>>;
	}
	template <typename T, bool rvalue = false>
	using reference_wrapper = detail::reference_wrapper<T, value_t<rvalue>>;

	template <typename T>
	using clref_t = reference_wrapper<const T>;

	PP_FUNCTOR(unref, auto&& x) -> decltype(auto)
	{
		if constexpr (PP_DECLTYPE(x)->Template == Template<detail::reference_wrapper>)
			return x.get();
		else
			return PP_FORWARD(x);
	}};

	constexpr inline auto ref = functor{ []
	(auto&& x)
	{
		return detail::reference_wrapper(PP_FORWARD(x));
	}} | unref;
}
