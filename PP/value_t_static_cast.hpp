#pragma once
#include <PP/get_value.hpp>
#include <PP/static_cast.hpp>
#include <PP/value_t.hpp>

namespace PP
{
PP_CIA value_t_static_cast =
    [](concepts::type auto&& t, concepts::value auto&& v)
{
    return value<static__cast(t, PP_GV(v))>;
};
}
