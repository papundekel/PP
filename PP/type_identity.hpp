#pragma once

namespace PP
{
	template <typename T>
	struct type_identity
	{
		using type = T;
	};

	#define PP_NEW_TYPE(o, T) decltype(o){ ::PP::type_identity<T>{} }
}
