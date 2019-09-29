#pragma once
template <typename T, typename... U>
constexpr auto same = (same<T, U> && ...);
template <typename T, typename U>
constexpr auto same<T, U> = false;
template <typename T>
constexpr auto same<T, T> = true;