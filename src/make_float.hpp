#pragma once
#include "make_type.hpp"
#include "fundamental_floats.hpp"

template <typename T>
using make_float = make_type<fundamental_floats, T>;