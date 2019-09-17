#pragma once
#include "ordered.hpp"
#include "invertible.hpp"

template <typename T>
constexpr auto signed_type(T t) { return ordered(t) && invertible(t) && -static_cast<untype<T>>(1) < static_cast<untype<T>>(0); }