#pragma once
#include <PP/get_type.hpp>
#include <PP/utility/forward.hpp>

namespace PP
{
PP_CIA static__cast = [](concepts::type auto&& t,
                         auto&& value) -> decltype(auto)
{
    return static_cast<PP_GT(t)>(PP_F(value));
};
}
