#pragma once

namespace PP::pack
{
PP_CIA any = [](auto&& p, auto&&... e) -> decltype(auto)
{
    return (false || ... || PP_F(p)(PP_F(e)));
};
}
