#pragma once
#include <PP/get_type.hpp>
#include <PP/value_t.hpp>

namespace PP
{
PP_CIA type_to_value = [](concepts::type auto&& t)
{
    return PP::value<PP_CT(t)>;
};
}
