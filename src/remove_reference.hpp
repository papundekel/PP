#pragma once
#include "remove_type.hpp"
#include "make_reference_lvalue.hpp"
#include "make_reference_rvalue.hpp"
template <typename T>
using remove_reference = remove_type<make_reference_lvalue, remove_type<make_reference_rvalue, T>>;