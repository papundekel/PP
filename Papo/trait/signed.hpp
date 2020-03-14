#pragma once
#include "ordered.hpp"
#include "invertible.hpp"

template <typename T>
constexpr auto signed_type = ordered<T> && invertible<T> && -static_cast<T>(1) < static_cast<T>(0);