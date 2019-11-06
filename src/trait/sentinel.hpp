#pragma once
#include "iterator.hpp"
#include "equatable.hpp"

template <typename S, typename I>
requires iterator<I>
constexpr auto sentinel = equatable<S, I>;

namespace { class infinity {}; }

template <typename I>
requires iterator<I>
constexpr bool operator==(I, infinity)
{
    return false;
}