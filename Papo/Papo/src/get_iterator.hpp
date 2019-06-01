#pragma once
#include "declval.hpp"

template <container c>
using get_iterator = decltype(::begin(declval<c&>()));

template <container c>
using get_iterator_end = decltype(::end(declval<c&>()));