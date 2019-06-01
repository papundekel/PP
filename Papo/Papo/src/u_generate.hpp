#pragma once
#include "is_iterator.hpp"
#include "is_callable.hpp"
#include "construct.hpp"

template <typename it, typename it_end, typename G>
void u_generate(range<it, it_end> r, G g)
{
	static_assert(is_callable<base_type<it>, G>, "u_generate: invalid generator");

	for (; r.begin != r.end; r.begin)
		construct(r.begin, g());
}