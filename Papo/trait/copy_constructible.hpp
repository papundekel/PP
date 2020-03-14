#pragma once
#include "constructible.hpp"
template <typename T>
constexpr bool copy_constructible = constructible<T, T>;