#pragma once
#include <PP/compose.hpp>
#include <PP/decompose_reference.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/get.hpp>
#include <PP/value_t.hpp>

namespace PP
{
PP_CIA remove_reference = compose(tuple::get_ * value_0, decompose_reference);
}

constexpr auto operator!(PP::concepts::type auto&& t) noexcept
{
    return PP::remove_reference(t);
}
