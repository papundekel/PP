#pragma once
#include "iterator.hpp"
#include "decrementable.hpp"

template <typename T>
using iterator_bi = AND<iterator<T>, decrementable<T>>;