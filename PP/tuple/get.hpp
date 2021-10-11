#pragma once
#include "../functor.hpp"
#include "../get_value.hpp"
#include "../type_t.hpp"
#include "../utility/forward.hpp"

namespace PP::functors
{
PP_CIA tuple_get =
    [](concepts::value auto i, auto&& t) -> decltype(auto) requires requires
{
    PP_F(t)[i];
}
{
    return PP_F(t)[i];
};
}

namespace PP
{
using functors::tuple_get;
}
