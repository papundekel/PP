#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "assignable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"

template <equatable_c I>
concept iterator_c = requires(I i)
{
	{ *i } -> auto&&;
} && incrementable_c<I>;

template <iterator_c I, typename T>
concept iterator_assignable_c = requires(I i)
{
	{ *i } -> assignable_to_c<T>;
};

template <iterator_c I, typename T>
concept iterator_convertible_c = requires(I i)
{
	{ *i } -> convertible_to_c<T>;
};

template <iterator_c I, typename T>
concept iterator_strict_c = requires(I i)
{
	{ *i } -> almost_c<T>;
};

template <iterator_c I>
using base = remove_reference<decltype(*declval<I>())>;