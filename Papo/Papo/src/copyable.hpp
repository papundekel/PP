#pragma once
#include "convertible.hpp"
template <typename T>
concept copyable = convertible_to<T, T>;