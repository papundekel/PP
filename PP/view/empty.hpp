#pragma once
#include "../empty_iterator.hpp"

namespace PP::view
{
template <typename T>
struct empty {
    constexpr empty_iterator<T> begin() const noexcept
    {
        return {};
    }
    constexpr empty_iterator<T> end() const noexcept
    {
        return {};
    }
};
}
