#pragma once
#include "compressed_pair.hpp"

namespace PP
{
template <typename Head, typename I>
class prepend_iterator
{
	Head& head;
	I i;
	bool at_head;

public:
	constexpr prepend_iterator(Head& head, I i)
	    : head(head)
	    , i(i)
};
}
