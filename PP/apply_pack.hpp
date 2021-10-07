#pragma once
#include "functor.hpp"
#include "functor_concept.hpp"
#include "value_sequence.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA apply_pack =
    functor([]<auto... I>(auto&& packer, auto&& selector, value_sequence<I...>)
                ->decltype(auto)
            {
                return PP_F(packer)(PP_F(selector)(value<I>)...);
            });
}
