#pragma once
#include <PP/get_type.hpp>
#include <PP/templated_dummy.hpp>

namespace PP
{
PP_CIA is_complete_object = [](concepts::type auto&& t)
{
    return requires
    {
        typename detail::templated_dummy<PP_GT(t)[]>;
    };
};
}
