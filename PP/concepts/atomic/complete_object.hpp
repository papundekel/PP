#pragma once
#include "../../functor.hpp"
#include "../../get_type.hpp"
#include "../../templated_dummy.hpp"

namespace PP
{
namespace functors
{
PP_CIA is_complete_object = [](concepts::type auto t)
{
    return requires
    {
        typename detail::templated_dummy<PP_GT(t)[]>;
    };
};
}
PP_FUNCTOR(is_complete_object)
}
