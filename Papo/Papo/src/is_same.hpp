#pragma once

template <typename T, typename U> constexpr bool is_same	   = false;
template <typename T>			  constexpr bool is_same<T, T> =  true;