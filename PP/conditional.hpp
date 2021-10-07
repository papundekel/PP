#pragma once
#include "functor.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "type_t.hpp"

namespace PP
{
PP_FUNCTOR(conditional,
           concepts::value auto condition,
           auto&& true_value,
           auto&& false_value) -> decltype(auto)
{
    if constexpr (PP_GV(condition))
        return PP_F(true_value);
    else
        return PP_F(false_value);
});
}
