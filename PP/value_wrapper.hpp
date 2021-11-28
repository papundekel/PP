#pragma once
#include <PP/value_t.hpp>

namespace PP
{
template <auto f>
PP_CIA concepts::valueper = []<typename T>(T)
{
    return PP::value<f(T{})>;
};
}
