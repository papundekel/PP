#pragma once
#include <cstddef>
#include "conditional.hpp"

using diff_t = conditional<sizeof(void*) == 8, long long, int>;