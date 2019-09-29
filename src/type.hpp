#pragma once
#include <cstddef>
template <typename... T>
struct types
{
    using first = types<>;
    using rest = types<>;
};

template <typename T, typename... U>
struct types<T, U...>
{
    using first = T;
    using rest = types<U...>;
};

template <typename T>
using type = types<T>;

template <typename T>
using first = typename T::first;
template <typename T>
using rest = typename T::rest;

namespace dtypescount
{   template <typename... T>
    constexpr auto x(types<T...>) { return sizeof...(T); }}
template <typename T>
constexpr auto count = dtypescount::x(T{});

template <auto T>
using decl_type = untype<decltype(T())>;

template <auto L>
struct wrap
{
	template <typename... T>
    static constexpr auto x = L(type<T>{}...);
    template <typename... T>
    using y = decl_type<x<T...>>;
};

namespace dwrapper
{
    template <template <typename...> typename T, typename... U>
    struct x
    {
        template <typename... V>
        using y = T<U..., V...>;
    };
}
#define wrapper(...) dwrapper::x<__VA_ARGS__>::template y