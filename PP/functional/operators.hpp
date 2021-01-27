#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(neg, auto&& x) -> decltype(auto)
	{
		return !PP_FORWARD(x);
	}};
	PP_FUNCTOR(eql, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) == PP_FORWARD(y);
	}};
	PP_FUNCTOR(lst, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) <  PP_FORWARD(y);
	}};
	PP_FUNCTOR(lte, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) <= PP_FORWARD(y);
	}};
	PP_FUNCTOR(or_, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) || PP_FORWARD(y);
	}};
	PP_FUNCTOR(an_, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) && PP_FORWARD(y);
	}};
	PP_FUNCTOR(cal, auto&& f, auto&&... args) -> decltype(auto)
	{
		return PP_FORWARD(f)(PP_FORWARD(args)...);
	}};
}
