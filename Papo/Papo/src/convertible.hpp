#pragma once
template <typename From, typename To>
concept convertible_to = requires (From from)
{
    { from } -> To;
};