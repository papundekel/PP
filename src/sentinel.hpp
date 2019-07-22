#pragma once
#include "iterator.hpp"
#include "equatable.hpp"

template <typename S, iterator I>
concept sentinel = equatable_with<I, S>;

class infinity {};

template <iterator I>
constexpr bool operator==(I i, infinity j)
{
    return false;
}