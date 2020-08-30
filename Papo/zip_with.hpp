#pragma once
#include <tuple>
#include "view.hpp"

namespace Papo
{
	template <typename F, view... Views>
	constexpr void zip_with(F&& f, Views&&... views) noexcept(noexcept(std::declval<F>()(std::declval<view_base_t<Views>>()...)))
	{
		for (auto begins = std::make_tuple(begin(views)...);
			std::apply([&views...](const auto&... i) { return ((i != end(std::forward<Views>(views))) && ...); }, begins);
			std::apply([](auto&... i) { (++i, ...); }, begins))
			std::apply([&f](const auto&... i) { std::forward<F>(f)(*i...); }, begins);
	}
}
