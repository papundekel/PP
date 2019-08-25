#pragma once
#include "conditional_transform.hpp"
#include "ignore_type.hpp"
template <bool test, typename T, typename U>
using conditional = conditional_transform<test, ignore<T>::template type, U>;