#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "assignable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"

template <equatable I>
concept iterator = requires(I i)
{
	{ *i } -> auto&&;
} && incrementable<I>;

template <iterator I, typename T>
concept iterator_assignable = requires(I i)
{
	{ *i } -> assignable_to<T>;
};

template <iterator I, typename T>
concept iterator_convertible = requires(I i)
{
	{ *i } -> convertible_to<T>;
};

template <iterator I, typename T>
concept iterator_strict = requires(I i)
{
	{ *i } -> almost<T>;
};

namespace detail
{
	template <iterator I>
	constexpr auto base_type() -> remove_reference<decltype(*declval<I>())>;
}

template <typename T>
using base_type = decltype(detail::base_type<T>());