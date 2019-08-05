#pragma once
#include "iterator.hpp"
#include "equatable.hpp"

template <typename S, iterator_c I>
concept sentinel_c = equatable_with_c<I, S>;

class infinity {};

template <iterator_c I>
constexpr bool operator==(I i, infinity j)
{
    return false;
}