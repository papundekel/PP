#pragma once
#include "functor.hpp"
#include "macros/CIA.hpp"
#include "type_t.hpp"

namespace PP
{
namespace functors
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
using functors::decl_type_copy;
using functors::decl_type_forward;
}
