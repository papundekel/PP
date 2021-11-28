#pragma once
#include <PP/get_value.hpp>

namespace PP
{
template <typename Value>
struct extract_value
{
    static constexpr decltype(auto) value_f() noexcept
    {
        return get_value<Value>();
    }
};
}
