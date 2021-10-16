#pragma once
#include "get_type.hpp"

namespace PP
{
PP_CIA alignment_of = [](concepts::type auto&& t)
{
    return alignof(PP_GT(t));
};
}
