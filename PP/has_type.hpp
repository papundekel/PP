#pragma once

namespace PP::detail
{
	template <typename T>
	concept has_type = requires
	{
		typename T::type;
	};
}
