#pragma once
#include "../../get_type.hpp"
#include "../../templated_dummy.hpp"

namespace PP
{
PP_CIA is_pointable = [](concepts::type auto t)
{
    return requires
    {
        typename detail::templated_dummy<PP_GT(t)*>;
    };
};
}
