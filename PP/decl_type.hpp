#pragma once
#include <PP/macros/CIA.hpp>
#include <PP/type_t.hpp>

namespace PP
{
PP_CIA decl_type_copy = [](auto v)
{
    return PP_DT(v);
};
PP_CIA decl_type_forward = [](auto&& v)
{
    return PP_DT(v);
};
}
