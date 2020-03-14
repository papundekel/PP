#pragma once
#include "val.hpp"

namespace dclass_type
{
    template <typename T>
    constexpr auto x(void* T::*) { return true; }
    template <typename T>
    constexpr auto x(...) { return false; }
}

template <typename T>
using class_type = val<dclass_type::x<T>(nullptr)>;