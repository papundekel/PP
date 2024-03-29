#pragma once
#include <PP/tuple/find.hpp>

namespace PP::tuple
{
PP_CIA find_get = [](auto&& p, concepts::tuple auto&& tuple) -> decltype(auto)
{
    return PP_F(tuple)[find(PP_F(p), PP_F(tuple))];
};
}
