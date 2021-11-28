#pragma once
#include <PP/get_type.hpp>
#include <PP/placeholder.hpp>
#include <PP/pointer_base.hpp>

namespace PP
{
template <typename T>
class pointer_new : public pointer_base<T>
{
public:
    using pointer_base<T>::pointer_base;

    constexpr pointer_new(
        const pointer_new<detail::pointer_new_compatible<T> auto>&
            other) noexcept
        : pointer_base<T>(other.ptr)
    {}

private:
    constexpr pointer_new(placeholder_t, auto&&... args)
        : pointer_base<T>(new T(PP_F(args)...))
    {}

public:
    static constexpr auto create(auto&&... args)
    {
        return pointer_new(placeholder, PP_F(args)...);
    }

    constexpr void deallocate()
    {
        delete this->ptr;
    }
};
}
