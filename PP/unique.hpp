#pragma once
#include <utility>
#include "compressed_pair.hpp"
#include "constructible.hpp"
#include "different_cvref.hpp"
#include "exchange.hpp"
#include "placeholder.hpp"

namespace PP
{
	template <typename T>
	struct default_defaulter
	{
		T operator()() const
		{
			return {};
		}
	};

	template <typename T, typename Defaulter = default_defaulter<T>>
	class unique
	{
		compressed_pair<T, Defaulter> pair;

	public:
		constexpr unique()
			: pair{ Defaulter{}(), {} }
		{}


		template <typename D>
		constexpr unique(placeholder, D&& defaulter)
			: pair{ std::forward<D>(defaulter)(), std::forward<D>(defaulter) }
		{}

		constexpr unique(unique&& other) noexcept
			: pair{ PP::exchange(other.pair.first, other.pair.second()), std::move(other).pair.second }
		{}

		constexpr unique& operator=(unique&& other) noexcept
		{
			pair.first = PP::exchange(other.pair.first, other.pair.second());
			pair.second = std::move(other).pair.second;
			return *this;
		}

		constexpr T& get() noexcept
		{
			return pair.first;
		}
		constexpr const T& get() const noexcept
		{
			return pair.first;
		}
		constexpr T release() noexcept
		{
			return std::move(pair).first;
		}

		template <different_cvref<unique> U>
		constexpr unique(U&& value)
			: pair{ std::forward<U>(value), {} }
		{}
		template <different_cvref<unique> U, typename D>
		constexpr unique(U&& value, D&& defaulter)
			: pair{ std::forward<U>(value), std::forward<D>(defaulter) }
		{}
	};
}
