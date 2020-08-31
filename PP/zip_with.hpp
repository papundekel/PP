#pragma once
#include <tuple>
#include <type_traits>
#include "view.hpp"
#include "declval.hpp"

namespace PP
{
	template <typename F, view... Views>
	constexpr void zip_with(F&& f, Views&&... views) noexcept(std::is_nothrow_invocable_v<F, view_base_t<Views>...>)
	{
		for (
			auto begins = std::make_tuple(begin(views)...);
			std::apply([&views...](const auto&... i) { return ((i != end(std::forward<Views>(views))) && ...); }, begins);
			std::apply([](auto&... i) { (++i, ...); }, begins))
				std::apply([&f](const auto&... i) { std::forward<F>(f)(*i...); }, begins);
	}
}
