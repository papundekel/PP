#pragma once
#include "iterator.hpp"
#include "decrementable.hpp"

template <typename T>
constexpr auto iterator_bi = iterator<T> && decrementable<T>;