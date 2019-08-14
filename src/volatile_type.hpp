#pragma once
#include "make_volatile.hpp"
#include "has_projective_trait.hpp"
template <typename T>
using volatile_type = has_projective_trait<T, make_volatile>;