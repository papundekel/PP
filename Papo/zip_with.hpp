#pragma once
#include <tuple>
#include "view.hpp"

namespace Papo
{
	template <typename F, Papo::view... Views>
	constexpr void zip_with(F&& f, Views&&... views)
	{
		for (auto begins = std::make_tuple(Papo::begin(views)...);
			std::apply([&views...](const auto&... i) { return ((i != Papo::end(std::forward<Views>(views))) && ...); }, begins);
			std::apply([](auto&... i) { (++i, ...); }, begins))
			std::apply([&f](const auto&... i) { std::forward<F>(f)(*i...); }, begins);
	}
}
