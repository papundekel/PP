#pragma once

namespace PP
{
template <typename T>
struct arrow_operator_wrapper
{
    T obj;

    constexpr auto operator->() const
    {
        return &obj;
    }
};

constexpr auto make_arrow_operator_wrapper(auto initializer)
{
    return arrow_operator_wrapper<decltype(initializer())>{initializer()};
}
}
