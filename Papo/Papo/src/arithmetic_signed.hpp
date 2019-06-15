#pragma once
#include "arithmetic.hpp"
template <arithmetic A>
concept arithmetic_signed = requires(A a)
{
	{ -a } -> A;
} && static_cast<A>(-1) < static_cast<A>(0);