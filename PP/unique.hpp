#pragma once
//#include "arg_splitter.hpp"
#include "compressed_pair.hpp"
#include "concepts/constructible.hpp"
#include "construct_pack.hpp"
#include "decompose_template.hpp"
#include "exchange.hpp"
#include "in_place_tag.hpp"
#include "placeholder.hpp"
#include "remove_reference.hpp"
#include "tuple_splits.hpp"
#include "utility/forward.hpp"
#include "utility/move.hpp"

namespace PP
{
	struct default_releaser
	{
		template <typename T>
		constexpr auto operator()(T& x)
		{
			return exchange(x, T());
		}
	};
	struct move_releaser
	{
		constexpr auto operator()(auto& x)
		{
			return move(x);
		}
	};

	//constexpr inline struct unique_in_place_delimiter_t {} unique_in_place_delimiter;

	constexpr inline struct unique_default_releaser_tag_t {} unique_default_releaser_tag;

	template <typename T, typename Releaser = move_releaser>
	class unique
	{
		//static constexpr auto splitter = arg_splitter * type<unique_in_place_delimiter_t> * type_tuple<T, Releaser>;

		template <typename, typename>
		friend class unique;

		compressed_pair<T, Releaser> pair;

	public:
		//constexpr unique(in_place_tag_t, auto&&... args)
		//	: pair
		//	(
		//		splitter(value_0, PP_FORWARD(args)...),
		//		splitter(value_1, PP_FORWARD(args)...)
		//	)
		//{}
		constexpr unique(in_place_tag_t, auto&& releaser, auto&&... args)
			: pair(T(PP_FORWARD(args)...), PP_FORWARD(releaser))
		{}
		constexpr unique(unique_default_releaser_tag_t, auto&&... args)
			: unique(in_place_tag, Releaser(), PP_FORWARD(args)...)
		{}
		unique() = default;
		constexpr unique(placeholder_t, auto&& value, auto&& releaser)
			: pair(PP_FORWARD(value), PP_FORWARD(releaser))
		{}
		constexpr unique(const unique& other)
			: pair(other.pair.first, other.pair.second)
		{}
		template <typename U, typename D>
		constexpr unique(const unique<U, D>& other)
			: pair(other.pair.first, other.pair.second)
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

		constexpr auto& get_object() noexcept
		{
			return pair.first;
		}
		constexpr auto& get_object() const noexcept
		{
			return pair.first;
		}
		constexpr auto& get_releaser() noexcept
		{
			return pair.second;
		}
		constexpr auto& get_releaser() const noexcept
		{
			return pair.second;
		}

		constexpr T release() noexcept
		{
			return pair.second(pair.first);
		}
	};

	PP_FUNCTOR(make_unique_default, auto&& value)
	{
		constexpr auto value_type = ~PP_DECLTYPE(value);

		return Template<unique>(value_type)(unique_default_releaser_tag, PP_FORWARD(value));
	});
}
