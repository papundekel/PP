#pragma once
#include "conditional.hpp"

template <typename T>
constexpr auto declval() noexcept -> conditional<reference_rvalue<T>, T&&, T&>;