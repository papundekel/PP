#pragma once
#include "conditional_transform.hpp"
#include "ignore.hpp"


template <bool test, typename T, typename U>
using conditional = conditional_transform<test, wrapper(ignore, T), U>;