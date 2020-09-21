#pragma once
#include <utility>
#include "view.hpp"
#include "functional/id.hpp"

namespace PP
{
	constexpr inline auto all_of = []<view View, typename Predicate = decltype(id_weak)&>(View && v, Predicate && p = id_weak)
	{
		for (auto&& e : std::forward<View>(v))
			if (!std::forward<Predicate>(p)(e))
				return false;
		return true;
	};
}
