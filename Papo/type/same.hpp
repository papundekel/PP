#pragma once
#include "../type.hpp"
template <typename T>
constexpr auto operator==(type<T>, type<T>)
{
    return true;
}
template <typename T, typename U>
constexpr auto operator==(type<T>, type<U>)
{
    return false;
}
constexpr auto same = []
(auto x)
{
    return [x](auto y){ return x == y; };
};