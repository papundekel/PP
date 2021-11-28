#pragma once
#include <PP/declval.hpp>
#include <PP/get_type.hpp>
#include <PP/type_t.hpp>
#include <PP/utility/forward.hpp>

namespace PP
{
PP_CIA init_type = [](concepts::type auto&& t)
{
    return PP_DT(declval(PP_F(t))());
};
}
