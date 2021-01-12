#pragma once
#include <utility>

#include "compressed_pair.hpp"
#include "concepts/constructible.hpp"
#include "exchange.hpp"
#include "placeholder.hpp"

namespace PP
{
	template <typename T, typename Defaulter>
	class unique;

	namespace detail
	{
		template <typename T>
		constexpr inline bool is_unique = false;
		template <typename T, typename Defaulter>
		constexpr inline bool is_unique<unique<T, Defaulter>> = true;
	}

	template <typename T>
	struct default_defaulter
	{
		default_defaulter() = default;
		template <typename U>
		constexpr default_defaulter(U&&) noexcept
		{}

		constexpr T operator()() const
		{
			return {};
		}
	};

	template <typename T, typename Defaulter = default_defaulter<T>>
	class unique
	{
		template <typename U, typename D>
		friend class unique;

		compressed_pair<T, Defaulter> pair;

	public:
		constexpr unique()
			: pair{ Defaulter{}(), {} }
		{}

		template <typename D>
		constexpr unique(placeholder_t, D&& defaulter)
			: pair(std::forward<D>(defaulter)(), std::forward<D>(defaulter))
		{}

		template <typename U, typename D>
		constexpr unique(unique<U, D>&& other) noexcept
			: pair(PP::exchange(other.pair.first, other.pair.second()), std::move(other).pair.second)
		{}

		constexpr auto& operator=(unique&& other) noexcept
		{
			pair.first = PP::exchange(other.pair.first, other.pair.second());
			pair.second = std::move(other).pair.second;
			return *this;
		}

		constexpr auto& inner() noexcept
		{
			return pair.first;
		}
		constexpr auto& inner() const noexcept
		{
			return pair.first;
		}
		constexpr auto release() noexcept
		{
			return PP::exchange(std::move(pair).first, pair.second());
		}

		template <typename U>
		requires (!detail::is_unique<std::remove_cvref_t<U>>)
		constexpr unique(U&& value)
			: pair(std::forward<U>(value), {})
		{}
		template <typename U, typename D>
		requires (!detail::is_unique<std::remove_cvref_t<U>>)
		constexpr unique(U&& value, D&& defaulter)
			: pair(std::forward<U>(value), std::forward<D>(defaulter))
		{}
	};
}
