#pragma once
#include "one_of.hpp"

template <typename T>
concept character = one_of<T, char, wchar_t, char8_t, char16_t, char32_t>;