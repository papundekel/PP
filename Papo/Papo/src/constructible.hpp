#pragma once
template <typename T, typename ...Args>
concept constructible = requires (Args... args)
{
    T(args...);
};