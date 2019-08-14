#pragma once
#include "make_const.hpp"
#include "has_projective_trait.hpp"
template <typename T>
using const_type = has_projective_trait<T, make_const>;