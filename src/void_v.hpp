#pragma once
#include "void_t.hpp"
template<typename ...args>
constexpr void_t<> void_v(args...){}