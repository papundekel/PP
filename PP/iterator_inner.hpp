#pragma once

namespace PP
{
constexpr auto iterator_inner(auto i)
{
	if constexpr (requires
	              {
		              i.inner_iterator();
	              })
		return i.inner_iterator();
	else
		return i;
}
}
