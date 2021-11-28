#pragma once
#include <PP/compose.hpp>
#include <PP/decompose_volatile.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/get.hpp>
#include <PP/value_t.hpp>

namespace PP
{
PP_CIA get_volatile_value_t =
    compose(tuple::get_ * value_1, decompose_volatile);
}
