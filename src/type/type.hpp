#pragma once

template <typename... T>
struct type
{
    static constexpr auto _ = type{};
};

template <typename T>
constexpr type<T> t;

template <auto x>
using get_type = decltype([]<typename T>(type<T>) -> T {}(x));

template <auto l, typename T>
using trans = get_type<l(t<T>)>;