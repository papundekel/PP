#pragma once
template <typename From, typename To>
concept convertible_to = requires (const From from)
{
    To(from);
};

namespace detail
{
    template <typename To> constexpr void g(To to) {}
}

template <typename From, typename To>
concept implicitly_convertible_to = requires (From from)
{
    detail::g<To>(from);
};