#pragma once
#include "ordered.hpp"

template <ordered T>
concept number_signed = -static_cast<T>(1) < static_cast<T>(0);