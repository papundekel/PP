#pragma once
#include "../functor.hpp"
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"

namespace PP
{
namespace functors
{
PP_CIA is_union = [](concepts::type auto t)
{
    return __is_union(PP_GT(t));
};
}
PP_FUNCTOR(is_union)

PP_CONCEPT(union_type, union)
}
