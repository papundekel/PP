#pragma once
template <typename T>
constexpr bool is_small = sizeof(T) <= sizeof(void*);