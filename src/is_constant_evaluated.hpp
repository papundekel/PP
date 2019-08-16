#pragma once

constexpr inline bool is_constant_evaluated() noexcept
{
    return

    #ifdef __clang__
    false;

    #elif defined(__GNUG__)
    __builtin_is_constant_evaluated();

    #elif defined(_MSC_VER)
    false;
    
    #endif
}