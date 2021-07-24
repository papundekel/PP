#pragma once
#include "../apply_partially.hpp"
#include "../declval.hpp"
#include "../tuple/apply.hpp"

namespace PP
{
PP_FUNCTOR(is_invocable_pack,
           concepts::type auto f,
           concepts::type auto... arg_types)
{
	return requires
	{
		declval(f)(declval(arg_types)...);
	};
});

PP_FUNCTOR(is_invocable, concepts::type auto f, concepts::tuple auto arg_tuple)
{
	return (is_invocable_pack * f)[arg_tuple];
});

namespace concepts
{
template <typename F, typename... Args>
concept invocable = is_invocable_pack(PP::type<F>, PP::type<Args>...);
}
}
