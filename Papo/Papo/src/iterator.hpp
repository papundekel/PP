#pragma once
#include "declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "assignable.hpp"
#include "convertible.hpp"
#include "almost.hpp"
#include "remove_reference.hpp"

template <typename I>
concept iterator = requires(I i)
{
	{ *i } -> auto&&;
} && incrementable<I> && equatable<I>;

template <typename I, typename T>
concept iterator_assignable = requires(I i)
{
	{ *i } -> assignable_to<T>;
} && iterator<I>;

template <typename I, typename T>
concept iterator_convertible = requires(I i)
{
	{ *i } -> convertible_to<T>;
} && iterator<I>;

template <typename I, typename T>
concept iterator_strict = requires(I i)
{
	{ *i } -> almost<T>;
} && iterator<I>;

template <iterator I>
using base_t = remove_reference<decltype(*declval<I>())>;