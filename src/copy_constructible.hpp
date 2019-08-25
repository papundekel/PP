#pragma once
#include "constructible.hpp"
template <typename T>
using copy_constructible = constructible<T, T>;