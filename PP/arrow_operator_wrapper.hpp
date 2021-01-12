#pragma once
#include "forward.hpp"

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
}
