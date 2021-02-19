#pragma once
#include "arg_splitter.hpp"
#include "compressed_pair.hpp"
#include "concepts/constructible.hpp"
#include "construct_pack.hpp"
#include "decompose_template.hpp"
#include "exchange.hpp"
#include "placeholder.hpp"
#include "remove_reference.hpp"
#include "tuple_splits.hpp"
#include "utility/forward.hpp"
#include "utility/move.hpp"

namespace PP
{
	template <typename T>
	struct default_defaulter
	{
		default_defaulter() = default;

		template <typename U>
		constexpr default_defaulter(default_defaulter<U>&&) noexcept
		{}

		constexpr T operator()() const
		{
			return T();
		}
	};

	constexpr inline struct unique_in_place_tag_t {} unique_in_place_tag;
	constexpr inline struct unique_in_place_delimiter_t {} unique_in_place_delimiter;

	template <typename T, typename Defaulter = default_defaulter<T>>
	class unique
	{
		static constexpr auto unique_splitter = arg_splitter * type<unique_in_place_delimiter_t> * type_tuple<T, Defaulter>;

		template <typename, typename>
		friend class unique;

		compressed_pair<T, Defaulter> pair;

	public:
		constexpr unique(unique_in_place_tag_t, auto&&... args)
			: pair(
				unique_splitter(value_0, PP_FORWARD(args)...),
				unique_splitter(value_1, PP_FORWARD(args)...))
		{}
		constexpr unique()
			: unique(unique_in_place_tag, unique_in_place_delimiter)
		{}
		constexpr unique(placeholder_t, auto&& value, auto&& defaulter)
			: unique(unique_in_place_tag, PP_FORWARD(value), unique_in_place_delimiter, PP_FORWARD(defaulter))
		{}

		constexpr unique(unique&& other)
			: pair(other.release(), move(other).pair.second)
		{}
		template <typename U, typename D>
		constexpr unique(unique<U, D>&& other)
			: pair(other.release(), move(other).pair.second)
		{}

		constexpr unique& operator=(unique&& other)
		{
			pair.first = other.release();
			pair.second = move(other).pair.second;
			return *this;
		}
		template <typename U, typename D>
		constexpr unique& operator=(unique<U, D>&& other)
		{
			pair.first = other.release();
			pair.second = move(other).pair.second;
			return *this;
		}

		template <typename U, typename D>            unique(const unique<U, D>&) = delete;
		template <typename U, typename D> unique& operator=(const unique<U, D>&) = delete;

		constexpr T& get_object() noexcept
		{
			return pair.first;
		}
		constexpr const T& get_object() const noexcept
		{
			return pair.first;
		}
		constexpr T release() noexcept
		{
			return PP::exchange(pair.first, pair.second());
		}
	};

	PP_FUNCTOR(make_unique_default, auto&& value)
	{
		constexpr auto value_type = ~PP_DECLTYPE(value);
		constexpr auto defaulter_type = Template<default_defaulter>(value_type);

		return Template<unique>(value_type, defaulter_type)(placeholder, PP_FORWARD(value), defaulter_type());
	}};
}
