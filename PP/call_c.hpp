#pragma once
#include "call.hpp"
#include "macros/CIA.hpp"
#include "partial_.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_CIA call_c = [](auto&& f)
{
    return partial_c(call)(PP_F(f))();
};
}
