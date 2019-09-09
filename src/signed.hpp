#pragma once
#include "ordered.hpp"
#include "invertible.hpp"

template <typename T>
using signed_type = val<ordered<T>::v && invertible<T>::v && -static_cast<T>(1) < static_cast<T>(0)>;