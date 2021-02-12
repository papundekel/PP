#pragma once
#include "functional/functor.hpp"

namespace PP
{
	template <typename... Ts>
	struct overloaded : public Ts...
	{
		using Ts::operator()...;
	};
	template <typename... Ts>
	overloaded(Ts...)->overloaded<Ts...>;

	PP_FUNCTOR(make_overloaded_pack, auto&&... functors)
	{
		return functor{ overloaded{ PP_FORWARD(functors)... } };
	}};
}
