#pragma once
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"

namespace PP
{
PP_CIA is_union = [](concepts::type auto&& t)
{
    return __is_union(PP_GT(t));
};

PP_CONCEPT(union_type, union)
}
