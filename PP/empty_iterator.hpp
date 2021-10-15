#pragma once
#include "add_pointer.hpp"
#include "call.hpp"
#include "construct_pack.hpp"
#include "ptrdiff_t.hpp"

namespace PP
{
template <typename T>
struct empty_iterator
{
    constexpr auto& operator++() noexcept
    {
        return *this;
    }
    constexpr auto& operator--() noexcept
    {
        return *this;
    }
    constexpr T&& operator*() const noexcept
    {
        PP_GT(add_pointer <<= type<T>) p = nullptr;
        return static_cast<T&&>(*p);
    }
    constexpr auto& operator+=(ptrdiff_t) noexcept
    {
        return *this;
    }
    constexpr auto operator+(ptrdiff_t) const noexcept
    {
        return *this;
    }
    constexpr auto&& operator[](ptrdiff_t) const noexcept
    {
        return **this;
    }
    constexpr bool operator==(empty_iterator) const noexcept
    {
        return true;
    }
    constexpr ptrdiff_t operator-(empty_iterator) const noexcept
    {
        return 0;
    }

    constexpr operator auto() const
    {
        return (add_pointer <<= type<T>)(nullptr);
    }
};
}
