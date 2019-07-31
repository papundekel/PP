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
    ref(ref&&) = default;

    ref& operator=(const ref& other)
    {
        *ptr = *other.ptr;
        return *this;
    }
    ref& operator=(ref&& other)
    {
        *ptr = move(*other.ptr);
        return *this;
    }
    template <typename U>
    ref& operator=(U&& other)
    {
        *ptr = forward<U>(other);
        return *this;
    }

    operator T&()
    {
        return *ptr;
    }
};

template <typename T>
ref(T&) -> ref<T>;