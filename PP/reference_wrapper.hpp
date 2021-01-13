#pragma once
#include "decompose_template.hpp"
#include "remove_reference.hpp"
#include "apply_transform.hpp"

namespace PP
{
	template <typename T>
	struct reference_wrapper
	{
		apply_transform_t<remove_reference, T>* ptr;

		constexpr reference_wrapper(T&& ref) noexcept
			: ptr(&ref)
		{}

		constexpr T&& get() const noexcept
		{
			return static_cast<T&&>(*ptr);
		}
		constexpr operator T&&() const noexcept
		{
			return get();
		}
	};

	template <typename T>
	using clref_t = reference_wrapper<const T&>;

	PP_FUNCTOR(unref, auto&& x) -> decltype(auto)
	{
		if constexpr (PP_DECLTYPE(x)->Template == template_v<reference_wrapper>)
			return x.get();
		else
			return PP_FORWARD(x);
	}};
}
