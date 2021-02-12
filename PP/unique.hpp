#pragma once
#include "compressed_pair.hpp"
#include "concepts/constructible.hpp"
#include "construct_pack.hpp"
#include "decompose_template.hpp"
#include "exchange.hpp"
#include "placeholder.hpp"
#include "remove_reference.hpp"
#include "utility/forward.hpp"
#include "utility/move.hpp"

namespace PP
{
	template <typename T>
	struct default_defaulter
	{
		constexpr default_defaulter(auto&&...) noexcept
		{}

		constexpr T operator()() const
		{
			return {};
		}
	};

	template <typename T, typename Defaulter = default_defaulter<T>>
	class unique
	{
		template <typename, typename>
		friend class unique;

		compressed_pair<T, Defaulter> pair;

	public:
		constexpr unique(placeholder_t, auto&& value)
			: pair(PP_FORWARD(value), Defaulter{})
		{}
		constexpr unique(auto&& value, auto&& defaulter)
			: pair(PP_FORWARD(value), PP_FORWARD(defaulter))
		{}

		template <typename U, typename D>
		constexpr unique(unique<U, D>&& other)
			: pair(PP::exchange(other.pair.first, other.pair.second()), move(other).pair.second)
		{}

		template <typename U, typename D>
		constexpr auto& operator=(unique<U, D>&& other)
		{
			pair.first = PP::exchange(other.pair.first, other.pair.second());
			pair.second = move(other).pair.second;
			return *this;
		}

		constexpr auto& inner() noexcept
		{
			return pair.first;
		}
		constexpr const auto& inner() const noexcept
		{
			return pair.first;
		}
		constexpr auto release() noexcept
		{
			return PP::exchange(move(pair).first, pair.second());
		}
	};

	PP_FUNCTOR(make_unique_default, auto&& value)
	{
		constexpr auto value_type = ~PP_DECLTYPE(value);
		constexpr auto defaulter_type = Template<default_defaulter>(value_type);

		return Template<unique>(value_type, defaulter_type)(PP_FORWARD(value), defaulter_type());
	}};
}
