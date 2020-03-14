#pragma once
#include "move_.hpp"
#include "forward.hpp"

template <typename T>
class ref
{
    T* ptr;
public:
    template <typename U>
    requires requires (T* t, U&& u) { t = &u; }
    ref(U&& object)
        : ptr(&object)
    {}
    ref(const ref&) = default;

    operator T&()
    {
        return *ptr;
    }
};

template <typename T>
ref(T&) -> ref<T>;