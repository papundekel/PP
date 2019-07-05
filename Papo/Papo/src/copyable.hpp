#pragma once
#include "constructible.hpp"
template <typename T>
concept copyable = constructible<T, T&>;