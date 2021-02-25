#pragma once
#include "utility/forward.hpp"

namespace PP
{
	template <typename T>
	class arrow_operator_wrapper
	{
		T&& obj;

	public:
		constexpr arrow_operator_wrapper(T&& obj) noexcept
			: obj(PP_FORWARD(obj))
		{}

		constexpr auto operator->() const
		{
			return &obj;
		}
	};
	template <typename T>
	arrow_operator_wrapper(T&&) -> arrow_operator_wrapper<T>;
}
