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
#include "tags.hpp"
#include "tuple/splits.hpp"
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
struct zero_releaser
{
	constexpr auto operator()(auto& x)
	{
		return exchange(x, 0);
	}
};
struct nullptr_releaser
{
	constexpr auto operator()(auto& x)
	{
		return PP::exchange(x, nullptr);
	}
};
struct move_releaser
{
	constexpr auto operator()(auto& x)
	{
		return move(x);
	}
};

// constexpr inline struct movable_in_place_delimiter_t {}
// movable_in_place_delimiter;

constexpr inline struct movable_default_releaser_tag_t
{
} movable_default_releaser_tag;

template <typename T, typename Releaser = move_releaser>
class movable
{
	// static constexpr auto splitter = arg_splitter *
	// type<movable_in_place_delimiter_t> * type_tuple<T, Releaser>;

	template <typename, typename>
	friend class movable;

	compressed_pair<T, Releaser> pair;

public:
	// constexpr movable(in_place_tag_t, auto&&... args)
	//	: pair
	//	(
	//		splitter(value_0, PP_F(args)...),
	//		splitter(value_1, PP_F(args)...)
	//	)
	//{}
	constexpr movable(in_place_tag_t, auto&& releaser, auto&&... args)
	    : pair(T(PP_F(args)...), PP_F(releaser))
	{}
	constexpr movable(movable_default_releaser_tag_t, auto&&... args)
	    : movable(in_place_tag, Releaser(), PP_F(args)...)
	{}
	movable() = default;
	constexpr movable(placeholder_t, auto&& value, auto&& releaser)
	    : pair(PP_F(value), PP_F(releaser))
	{}
	constexpr movable(const movable& other)
	    : pair(other.pair.first, other.pair.second)
	{}
	template <typename U, typename D>
	constexpr movable(const movable<U, D>& other)
	    : pair(other.pair.first, other.pair.second)
	{}
	constexpr movable(movable&& other)
	    : pair(other.release(), move(other).pair.second)
	{}
	template <typename U, typename D>
	constexpr movable(movable<U, D>&& other)
	    : pair(other.release(), move(other).pair.second)
	{}

	constexpr movable& operator=(movable&& other)
	{
		if (this != &other)
		{
			pair.first = other.release();
			pair.second = move(other).pair.second;
		}

		return *this;
	}
	template <typename U, typename D>
	constexpr movable& operator=(movable<U, D>&& other)
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
	constexpr auto& operator[](tags::o_t) noexcept
	{
		return get_object();
	}
	constexpr auto& operator[](tags::o_t) const noexcept
	{
		return get_object();
	}
	constexpr auto& operator[](tags::r_t) noexcept
	{
		return get_releaser();
	}
	constexpr auto& operator[](tags::r_t) const noexcept
	{
		return get_releaser();
	}

	constexpr T release() noexcept
	{
		return pair.second(pair.first);
	}
};

PP_FUNCTOR(make_movable_default, auto&& value)
{
	constexpr auto value_type = ~PP_DT(value);

	return Template<movable>(value_type)(movable_default_releaser_tag,
	                                     PP_F(value));
});
}
