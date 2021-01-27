#pragma once
#include "apply_transform.hpp"
#include "concepts/reference.hpp"
#include "decompose_template.hpp"
#include "get_value.hpp"
#include "reference_wrapper.hpp"
#include "value_t.hpp"
#include "wrap_reference.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, typename C>
		struct array
		{
			static constexpr std::size_t count = -type<C>;

			T buffer[count];
		};
		array() -> array<char, value_t<0>>;
		template <typename T, typename... U>
		array(T, U...) -> array<T, value_t<sizeof...(U) + 1>>;
	}

	template <typename T, std::size_t count>
	using array = detail::array<apply_transform_t<wrap_reference, T>, value_t<count>>;

	PP_FUNCTOR(make_array, concepts::type auto t, auto&&... args)
	{
		if constexpr (PP_COPY_TYPE(t) == type<void>)
			return detail::array{ PP_FORWARD(args)... };
		else
			return detail::array<PP_GET_TYPE(t), value_t<sizeof...(args)>>{ PP_FORWARD(args)... };
	}};
	PP_FUNCTOR(forward_as_array, concepts::type auto t, auto&&... args)
	{
		if constexpr (PP_COPY_TYPE(t) == type<void>)
			return detail::array{ ref(PP_FORWARD(args))... };
		else
			return detail::array<reference_wrapper<PP_GET_TYPE(t)>, value_t<sizeof...(args)>>{ PP_FORWARD(args)... };
	}};


	namespace concepts
	{
		template <typename T>
		concept PP_array = PP::type<T>->Template == Template<PP::detail::array>;
	}

	constexpr auto begin(concepts::PP_array auto&& a) noexcept
	{
		return a.buffer;
	}
	constexpr auto end(concepts::PP_array auto&& a) noexcept
	{
		return a.buffer + a.count;
	}
}
