#pragma once
#include <PP/value_sequence.hpp>
#include <PP/value_t.hpp>

namespace PP
{
PP_CIA apply_pack =
    []<auto... I>(auto&& packer, auto&& selector, value_sequence<I...>)
        -> decltype(auto)
{
    return PP_F(packer)(PP_F(selector)(value<I>)...);
};
}
