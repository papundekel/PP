#pragma once
#include "concepts/reference.hpp"
#include "decompose_template.hpp"
#include "get_value.hpp"
#include "reference_wrapper.hpp"
#include "value_t.hpp"
#include "transform_view.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, typename C>
		struct array
		{
			static constexpr std::size_t count = -type_v<C>;

			T buffer[count];
		};
		array()->array<char, value_t<0>>;
		template <typename T, typename... U>
		array(T, U...) -> array<T, value_t<sizeof...(U) + 1>>;
	}
	template <typename T, std::size_t Count>
	using array = detail::array<PP_GET_TYPE([](auto t)
		{
			constexpr auto type = PP_COPY_TYPE(t);
			if constexpr (is_reference(type))
				return type_v<reference_wrapper<PP_GET_TYPE(type)>>;
			else
				return t;
		}(type_v<T>)), value_t<Count>>;

	PP_FUNCTOR(make_array, type_wrap auto t, auto&&... args)
	{
		if constexpr (PP_COPY_TYPE(t) == type_v<void>)
			return detail::array{ PP_FORWARD(args)... };
		else
			return detail::array<PP_GET_TYPE(t), value_t<sizeof...(args)>>{ PP_FORWARD(args)... };
	}};
	PP_FUNCTOR(forward_as_array, type_wrap auto t, auto&&... args)
	{
		if constexpr (PP_COPY_TYPE(t) == type_v<void>)
			return detail::array{ ref(PP_FORWARD(args))... };
		else
			return detail::array<reference_wrapper<PP_GET_TYPE(t)>, value_t<sizeof...(args)>>{ PP_FORWARD(args)... };
	}};


	namespace concepts
	{
		template <typename T>
		concept PP_array = type_v<T>->Template == template_v<PP::detail::array>;
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
