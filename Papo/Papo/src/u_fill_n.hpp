#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "construct.hpp"

template <typename it1, typename T>
enable_if<is_iterator<it1>,
void> u_fill_n(it1 destBegin, size_t count, const T& value)
{
	for (size_t i = 0; i != count; ++i, ++destBegin)
		construct(destBegin, value);
}