#pragma once
#include "ordered.hpp"
#include "invertible.hpp"

template <typename T>
struct signed_type : value_t<ordered<T>::v && invertible<T>::v && -static_cast<T>(1) < static_cast<T>(0)> {};