#pragma once
#include "find_t.hpp"

template <template <typename> typename F, typename ...T>
constexpr bool contains_t = find_t<F, T...> != sizeof...(T);