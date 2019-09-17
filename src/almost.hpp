#pragma once
#include "same.hpp"
#include "remove_cvref.hpp"

template <typename... T>
constexpr auto almost(T... t)
{
    return same(remove_cv(t)...);
}