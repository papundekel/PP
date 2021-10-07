#pragma once
#include "size_t.hpp"

namespace PP
{
template <typename T>
struct type_t
{
    using type = T;

    type_t() = default;
    type_t(const type_t&) = default;

    constexpr auto operator->() const noexcept;
    constexpr decltype(auto) operator()(auto&&...) const;
};

template <typename T>
constexpr inline type_t<T> type{};

constexpr inline type_t<void> type_void{};
constexpr inline type_t<int> type_int{};
constexpr inline type_t<char> type_char{};
constexpr inline type_t<size_t> type_size_t{};
}

template <typename T, typename U>
constexpr auto operator==(PP::type_t<T>, PP::type_t<U>) noexcept
{
    return false;
}

template <typename T>
constexpr auto operator==(PP::type_t<T>, PP::type_t<T>) noexcept
{
    return true;
}

#define PP_DT(x) (::PP::type<decltype(x)>)
