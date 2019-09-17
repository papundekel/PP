#pragma once
#include "conditional_transform.hpp"
#include "const_type.hpp"
#include "volatile_type.hpp"

template <typename T, typename Transform>
constexpr auto keep_volatile(Transform transform, T t)
{
    return conditional_transform<volatile_type(t)>([](auto x){ return make_volatile(x); }, t);
}

template <typename T, typename Transform>
constexpr auto keep_const(Transform transform, T t)
{
    return conditional_transform<const_type(t)>([](auto x){ return make_const(x); }, t);
}

template <typename T, typename Transform>
constexpr auto keep_cv(Transform transform, T t)
{
    return keep_const(transform, keep_volatile(transform, t));
}