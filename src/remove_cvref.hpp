#pragma once
#include "remove_reference.hpp"
#include "remove_cv.hpp"

template <typename T>
constexpr auto remove_cvref(T t) { return remove_reference(remove_cv(t));}