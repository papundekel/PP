#pragma once
#include "type.hpp"

constexpr auto size_of = []
<typename T>(type<T> x)
{ return sizeof(T); };