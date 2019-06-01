#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "construct.hpp"

template <typename it1, typename T>
enable_if<is_iterator<it1>,
void> u_fill(it1 destBegin, it1 destEnd, const T& value)
{
	for (; destBegin != destEnd; ++destBegin)
		construct(destBegin, value);
}