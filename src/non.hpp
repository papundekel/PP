#pragma once
#include "value_t.hpp"

template <template <typename...> typename Test, typename... Args>
struct non : value_t<!Test<Args...>::v> {};