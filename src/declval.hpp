#pragma once
#include "conditional.hpp"
#include "reference_rvalue.hpp"

template <typename T>
constexpr auto declval() noexcept -> conditional<reference_rvalue<T>::v, T&&, T&>;