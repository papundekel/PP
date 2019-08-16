#pragma once
#include "iterator.hpp"
#include "equatable.hpp"

template <typename S, typename I>
requires iterator<I>::v
struct sentinel : equatable_with<I, S> {};

class infinity {};

template <typename I>
requires iterator<I>::v
constexpr bool operator==(I, infinity)
{
    return false;
}