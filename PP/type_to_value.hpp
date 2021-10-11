#pragma once
#include "get_type.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA type_to_value = [](concepts::type auto t)
{
    return PP::value<PP_COPY_TYPE(t)>;
};
}
