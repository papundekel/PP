#pragma once
#include "iterator.hpp"
#include "decrementable.hpp"

template <iterator T>
concept iterator_bi = decrementable<T>;