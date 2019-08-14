#pragma once
#include "constructible.hpp"
template <typename T>
struct copy_constructible : constructible<T, T> {};