#pragma once
template <typename T>
struct ignore
{
    template <typename U>
    using type = T;
};