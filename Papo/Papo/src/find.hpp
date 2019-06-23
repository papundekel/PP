#pragma once
#include "equatable.hpp"
#include "base_type.hpp"
#include "range.hpp"

template <typename range_t, equatable_with<typename range_t::base_t> T>
auto find(range_t r, const T& value)
{
	for (; r.begin != r.end && *r.begin != value; ++r.begin);
	return r.begin;
}