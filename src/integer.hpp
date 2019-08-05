#pragma once

template <typename T>
constexpr bool integer_v = static_cast<T>(1) / static_cast<T>(2) == 0;

template <typename T>
concept integer_c = integer_v<T>;