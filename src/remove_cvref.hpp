#pragma once
#include "remove_reference.hpp"
#include "remove_cv.hpp"

template <typename T>
using remove_cvref = remove_cv<remove_reference<T>>;