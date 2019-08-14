#pragma once
#include "iterator.hpp"
#include "decrementable.hpp"

template <typename T>
struct iterator_bi : value_t<iterator<T>::v && decrementable<T>::v> {};