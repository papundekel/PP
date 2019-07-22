#pragma once
#include "ordered.hpp"
#include "invertible.hpp"

template <ordered T>
concept signed_t = invertible<T> && -static_cast<T>(1) < static_cast<T>(0);