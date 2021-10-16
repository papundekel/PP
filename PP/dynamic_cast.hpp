#pragma once
#include "get_type.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_CIA dynamic__cast = [](concepts::type auto&& t,
                          auto&& value) -> decltype(auto)
{
    return dynamic_cast<PP_GT(t)>(PP_F(value));
};
}
