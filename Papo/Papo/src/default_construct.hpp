#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "get_address.hpp"

template <typename T, typename it, typename it_end>
enable_if<is_iterator<it>
,void> default_construct(range<it, it_end> r)
{
	for (; r.begin != r.end; ++r.begin)
		new (get_address(r.begin)) T;
}