#pragma once
template <typename T>
struct ignore
{
    template <typename...>
    using type = T;
};