#pragma once
template <typename T>
constexpr auto ignore(T t, ...) { return t; }