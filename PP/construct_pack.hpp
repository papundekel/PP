#pragma once
#include "get_type.hpp"
#include "type_t.hpp"

namespace PP
{
PP_CIA construct_pack = [](concepts::type auto&& t,
                           auto&&... args) -> decltype(auto)
{
    return PP_GT(t)(PP_F(args)...);
};
}
