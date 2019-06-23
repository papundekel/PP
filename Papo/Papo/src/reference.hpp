#pragma once
#include "reference_lvalue.hpp"
#include "reference_rvalue.hpp"

template <typename T>
concept reference = reference_lvalue<T> || reference_rvalue<T>;