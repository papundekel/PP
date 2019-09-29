#pragma once
#include "remove_reference.hpp"
#include "remove_cv.hpp"
template <typename T>
using remove_cvref = remove_reference<remove_cv<T>>;