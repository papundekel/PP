#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "is_same.hpp"
#include "base_type.hpp"
#include "swap.hpp"

template <typename it1, typename it2>
enable_if<is_same<base_type<it1>, base_type<it2>>,
void> it_swap(it1 first, it2 second)
{ swap(*first, *second); }