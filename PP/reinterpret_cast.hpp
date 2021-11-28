#pragma once
#include <PP/get_type.hpp>
#include <PP/utility/forward.hpp>

namespace PP
{
PP_CIA reinterpret__cast = [](concepts::type auto&& t,
                              auto&& value) -> decltype(auto)
{
    return reinterpret_cast<PP_GT(t)>(PP_F(value));
};
}
