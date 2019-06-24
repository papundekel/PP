#pragma once
#include "same.hpp"
#include "remove_cvref.hpp"

template <typename T, typename U>
concept almost = same<remove_cvref<T>, remove_cvref<U>>;