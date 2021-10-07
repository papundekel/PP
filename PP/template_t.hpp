#pragma once

namespace PP
{
template <template <typename...> typename Template>
struct template_t
{
    constexpr auto operator[](auto&& types) const noexcept;
    constexpr auto operator()(auto... types) const noexcept;
};
template <template <typename...> typename T>
constexpr inline template_t<T> Template{};
}

template <template <typename...> typename T, template <typename...> typename U>
constexpr auto operator==(PP::template_t<T>, PP::template_t<U>) noexcept
{
    return false;
}
template <template <typename...> typename T>
constexpr auto operator==(PP::template_t<T>, PP::template_t<T>) noexcept
{
    return true;
}
