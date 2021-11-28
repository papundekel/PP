#pragma once
#include <PP/get_type.hpp>
#include <PP/templated_dummy.hpp>

namespace PP
{
PP_CIA is_class = [](concepts::type auto&& t)
{
    return requires
    {
        typename detail::templated_dummy<int PP_GT(t)::*>;
    };
};
}
