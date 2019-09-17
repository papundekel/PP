#pragma once
#include "ignore.hpp"
#include "type.hpp"

namespace dconstructible_template
{
	template <template <typename> typename T, typename... Args>
	constexpr bool x = false;
	template <template <typename> typename T, typename... Args>
	constexpr bool x<T, decl_type<ignore(type<void>{}, typeof(T(declval<Args>()...)))>, Args...> = true;
}
template <template <typename> typename T, typename... Args>
constexpr auto constructible_template(Args...) { return dconstructible_template::x<T, void, untype<Args>...>; }