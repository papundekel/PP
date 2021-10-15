#pragma once
#include "macros/CIA.hpp"
#include "type_t.hpp"

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
