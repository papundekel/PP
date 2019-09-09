#pragma once
#include "ignore_type.hpp"
#include "val.hpp"
#include "declval.hpp"
namespace dconstructible_template
{
	template <template <typename> typename T, typename... Args>
	constexpr bool x = false;
	template <template <typename> typename T, typename... Args>
	constexpr bool x<T, ignore<void>::type<decltype(T(declval<Args>()...))>, Args...> = true;
}
template <template <typename> typename T, typename... Args>
using constructible_template = val<dconstructible_template::x<T, void, Args...>>;