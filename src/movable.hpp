#pragma once
#include "constructible.hpp"
template <typename T>
concept movable = constructible<T, T&&>;