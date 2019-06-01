#pragma once
#include "iterator.hpp"
#include "decrementable.hpp"

template <typename T>
concept iterator_bi = iterator<T> && decrementable<T>;