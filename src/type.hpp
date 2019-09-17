#pragma once
#include <cstddef>
template <typename... T>
struct types {};

template <typename T>
struct types<T> { using t = T; };

template <typename T>
using type = types<T>;

template <typename T>
using untype = typename T::t;

template <auto T>
using decl_type = untype<decltype(T)>;

#define typeof(x) type<decltype( x )>{}