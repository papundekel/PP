#pragma once

template <typename T> constexpr bool is_const		   = false;
template <typename T> constexpr bool is_const<const T> = true;