#pragma once
#include "ignore.hpp"
#include "type.hpp"

namespace dconstructible_template
{
	template <template <typename> typename T, typename... Args>
	constexpr bool x = false;
	template <template <typename> typename T, typename... Args>
	constexpr bool x<T, decltype(T(declval<Args>()...), void()), Args...> = true;
}
template <template <typename> typename T, typename... Args>
constexpr auto constructible_template = dconstructible_template::x<T, void, Args...>;