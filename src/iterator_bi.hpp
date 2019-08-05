#pragma once
#include "iterator.hpp"
#include "decrementable.hpp"

template <iterator_c T>
concept iterator_bi_c = decrementable_c<T>;