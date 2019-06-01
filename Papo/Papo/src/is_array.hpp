#pragma once

template <typename T>			constexpr bool is_array		  = false;
template <typename T>			constexpr bool is_array<T[]>  =  true;
template <typename T, size_t N> constexpr bool is_array<T[N]> =  true;