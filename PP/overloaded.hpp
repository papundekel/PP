#pragma once
#include "functor.hpp"

namespace PP
{
	template <typename... Ts>
	struct overloaded
		: public Ts...
	{
		using Ts::operator()...;

#ifdef __clang__
		constexpr overloaded(auto&&... args)
			: Ts(PP_F(args))...
		{}
#endif
	};
	template <typename... Ts>
	overloaded(Ts...) -> overloaded<Ts...>;

	PP_FUNCTOR(make_overloaded_pack, auto&&... functors)
	{
		return functor(overloaded(unwrap_functor(PP_F(functors))...));
	});
}
