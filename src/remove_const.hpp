#pragma once
#include "remove_type.hpp"
#include "make_const.hpp"
template <typename T>
using remove_const = remove_type<make_const, T>;