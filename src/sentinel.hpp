#pragma once
#include "iterator.hpp"
#include "equatable.hpp"

template <typename S, typename I>
requires iterator(I{})
constexpr auto sentinel(S s, I i) { return equatable(s, i); }

class infinity {};

template <typename I>
requires iterator(I{})
constexpr bool operator==(I, infinity)
{
    return false;
}