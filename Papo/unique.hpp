#pragma once
#include <utility>
#include "compressed_pair.hpp"
#include "constructible.hpp"
#include "different_cvref.hpp"
#include "exchange.hpp"

namespace Papo
{
	template <constructible T>
	struct default_defaulter
	{
		T operator()() const
		{
			return {};
		}
	};

	template <typename T, typename Defaulter = default_defaulter<T>>
	struct unique
	{
		compressed_pair<T, Defaulter> pair;

		template <different_cvref<unique> U, typename D>
		constexpr unique(U&& value, D&& defaulter)
			: pair{ std::forward<U>(value), std::forward<D>(defaulter) }
		{}

		constexpr unique(unique&& other) noexcept
			: pair{ Papo::exchange(other.pair.first, other.pair.second()), std::move(other).pair.second }
		{}

		constexpr operator=(unique&& other) noexcept
		{
			pair.first = Papo::exchange(other.pair.first, other.pair.second());
			pair.second = std::move(other).pair.second;
		}

		constexpr T& get() noexcept
		{
			return value;
		}
	};
}
