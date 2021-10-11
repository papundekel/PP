#pragma once
#include "add_reference.hpp"
#include "get_reference.hpp"

namespace PP
{
PP_CIA copy_reference = [](concepts::type auto from, concepts::type auto to)
{
    return add_reference(get_reference_value_t(from), to);
};
}
