#pragma once

template <typename T>
constexpr size_t extent = 0;
template <typename T>
constexpr size_t extent<T[]> = 0;
template <typename T, size_t N>
constexpr size_t extent<T[N]> = N;

template <typename T, size_t N>
constexpr size_t extent_of(T(&)[N]) { return N; }