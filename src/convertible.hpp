#pragma once
template <typename From, typename To>
concept convertible_to_c = requires (const From from)
{
    To(from);
};

namespace detail
{
    template <typename To> constexpr void g(To to) {}
}

template <typename From, typename To>
concept implicitly_convertible_to_c = requires (From from)
{
    detail::g<To>(from);
};