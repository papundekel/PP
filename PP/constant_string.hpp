#pragma once
#include <PP/size_t.hpp>
#include <PP/view/copy.hpp>

namespace PP
{
template <size_t count>
struct constant_string
{
    char chars[count];

    constexpr constant_string(const char (&string)[count + 1]) noexcept
    {
        view::copy(chars, string);
    }
};
template <size_t count>
constant_string(const char (&)[count]) -> constant_string<count - 1>;
}
