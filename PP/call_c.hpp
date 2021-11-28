#pragma once
#include <PP/call.hpp>
#include <PP/macros/CIA.hpp>
#include <PP/partial_.hpp>
#include <PP/utility/forward.hpp>

namespace PP
{
PP_CIA call_c = [](auto&& f)
{
    return partial_c(call)(PP_F(f))();
};
}
