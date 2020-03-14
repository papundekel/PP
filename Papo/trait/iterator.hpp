#pragma once
#include "../utility/declval.hpp"
#include "equatable.hpp"
#include "incrementable.hpp"
#include "convertible.hpp"
#include "almost.hpp"

template <typename T>
constexpr auto iterator = requires (T i)
{
	{ *i } -> auto&;
};

constexpr auto base = t<decltype(*declval<I>())>.remove_ref;