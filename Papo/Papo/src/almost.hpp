#pragma once
#include "same.hpp"
#include "remove_cvref.hpp"

template <typename ...T>
concept almost = same<remove_cvref<T>...>;