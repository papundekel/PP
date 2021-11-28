#pragma once
#include <PP/get_value.hpp>
#include <PP/size_t.hpp>

namespace PP::pack
{
PP_CIA remove_first =
    [](concepts::value auto&& offset_v, auto&& f, auto&&... x) -> decltype(auto)
{
    constexpr auto offset = PP_GV(offset_v);

    return []
    {
        if constexpr (offset == 1)
            return [](auto&& f, auto&&, auto&&... x) -> decltype(auto)
            {
                return PP_F(f)(PP_F(x)...);
            };
        else if constexpr (offset == 2)
            return [](auto&& f, auto&&, auto&&, auto&&... x) -> decltype(auto)
            {
                return PP_F(f)(PP_F(x)...);
            };
        else if constexpr (offset == 3)
            return [](auto&& f, auto&&, auto&&, auto&&, auto&&... x)
                       -> decltype(auto)
            {
                return PP_F(f)(PP_F(x)...);
            };
        else if constexpr (offset == 4)
            return [](auto&& f, auto&&, auto&&, auto&&, auto&&, auto&&... x)
                       -> decltype(auto)
            {
                return PP_F(f)(PP_F(x)...);
            };
    }()(PP_F(f), PP_F(x)...);
};
}
