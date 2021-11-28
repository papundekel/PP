#pragma once
#include <PP/get_value.hpp>
#include <PP/value_t_static_cast.hpp>
#include <PP/tuple/count.hpp>
#include <PP/tuple/pred.hpp>

namespace PP::detail
{
constexpr decltype(auto) tuple_recursive(auto&& f,
                                         concepts::value auto&& i,
                                         auto&& t)
{
    if constexpr (*PP_CV(i) == 0)
        return PP_F(f)(PP_F(t));
    else
        return tuple_recursive(PP_F(f), i - value_1, tuple::pred(PP_F(t)));
}
}

namespace PP::tuple
{
// clang-format off
PP_CIA recursive = [](auto&& f, concepts::value auto&& i, auto&& t)
    -> decltype(auto) requires requires { PP_F(f)(PP_F(t)); }
                            && ((PP_CV(i) < type_count_value_t(PP_DT(t))).value_f())
	                  	    && (
                                   *PP_CV(i) == 0
                               ||  requires { pred(PP_F(t)); }
	                           )
{
	return detail::tuple_recursive(PP_F(f), i, PP_F(t));
};
// clang-format on
}
