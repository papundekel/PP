#pragma once
#include "../../functor.hpp"
#include "../../get_type.hpp"
#include "../../templated_dummy.hpp"

namespace PP
{
namespace functors
{
PP_CIA is_class = [](concepts::type auto t)
{
    return requires
    {
        typename detail::templated_dummy<int PP_GT(t)::*>;
    };
};
}
PP_FUNCTOR(is_class)
}
