#pragma once
#include <PP/get_type.hpp>

namespace PP
{
PP_CIA size_of = [](concepts::type auto&& t)
{
    return sizeof(PP_GT(t));
};
}
