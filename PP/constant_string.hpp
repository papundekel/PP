#pragma once
#include "size_t.hpp"
#include "view/copy.hpp"

namespace PP
{
template <PP::size_t count>
struct constant_string
{
    char chars[count];

    constexpr constant_string(const char (&string)[count + 1]) noexcept
    {
        PP::view_copy(chars, string);
    }
};
template <PP::size_t count>
constant_string(const char (&)[count]) -> constant_string<count - 1>;
}
