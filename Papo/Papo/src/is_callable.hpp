#pragma once
#include "declval.hpp"
#include "void_t.hpp"
#include <functional>

template <typename return_t, typename f, typename = void_t<>, typename ...args>
constexpr bool _is_callable = false;

template <typename return_t, typename f, typename ...args>
constexpr bool _is_callable<return_t, f, void_t<decltype(
	static_cast<return_t>(std::invoke(declval<f>(), declval<args>()...)))
>, args...> = true;

template <typename return_t, typename f, typename ...args>
constexpr bool is_callable = _is_callable<return_t, f, void, args...>;