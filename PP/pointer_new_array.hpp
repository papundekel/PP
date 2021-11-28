#pragma once
#include <PP/get_type.hpp>
#include <PP/pointer_base.hpp>
#include <PP/size_t.hpp>

namespace PP
{
template <typename T>
class pointer_new_array : public pointer_base<T>
{
public:
    using pointer_base<T>::pointer_base;

    explicit constexpr pointer_new_array(size_t count)
        : pointer_base<T>(new T[count])
    {}

    constexpr pointer_new_array(
        const pointer_new_array<detail::pointer_new_compatible<T> auto>&
            other) noexcept
        : pointer_base<T>(other.ptr)
    {}

    constexpr void deallocate()
    {
        delete[] this->ptr;
    }
};
}
