#pragma once
#include "conditional.hpp"
#include "reference_rvalue.hpp"

template <typename T>
constexpr auto declval() noexcept -> decl_type<conditional<reference_rvalue(type<T>{})>(type<T&&>{},  type<T&>{})>;

template <typename T>
constexpr auto declval(T) noexcept -> decltype(declval<untype<T>>());