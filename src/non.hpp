#pragma once
#include "value_t.hpp"

template <template <typename...> typename Test, typename... Args>
using non = value_t<!Test<Args...>::v>;