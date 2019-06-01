#pragma once
#include "is_same.hpp"
#include "remove_cv.hpp"

template <class _Ty>
constexpr bool is_nullptr_t = is_same<remove_cv<_Ty>, std::nullptr_t>;