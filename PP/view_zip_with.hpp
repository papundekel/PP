#pragma once
#include "functional/apply_partially.hpp"
#include "functional/compose_apply.hpp"
#include "functional/operators.hpp"
#include "tuple.hpp"
#include "tuple_all.hpp"
#include "tuple_apply.hpp"
#include "tuple_make.hpp"
#include "tuple_map.hpp"
#include "view.hpp"

namespace PP
{
	template <typename Transform, typename... Iterators>
	class zip_with_iterator
	{
		compressed_pair<tuple<Iterators...>, Transform> p;

	public:
		//constexpr zip_with_iterator()
		//constexpr decltype(auto)
	};

	PP_FUNCTOR(zip_with, auto&& f, concepts::tuple auto&& views)
	{
		auto begin_ends = view_begin_end + PP_FORWARD(views);
		auto begins = tuple_get * value_0 + begin_ends;
		for (; *neq && begin_ends; ipr + begins)
		{
			tuple_apply(PP_FORWARD(f), der + begins);
		}
		return tuple_make(begins);
	}};
}
