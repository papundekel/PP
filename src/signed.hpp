#pragma once
#include "ordered.hpp"
#include "invertible.hpp"

template <ordered_c T>
concept signed_c = invertible_c<T> && -static_cast<T>(1) < static_cast<T>(0);