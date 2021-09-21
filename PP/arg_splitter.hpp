#pragma once
#include "applier.hpp"
#include "construct_pack.hpp"
#include "get_type.hpp"
#include "tuple.hpp"
#include "tuple/apply.hpp"
#include "tuple/count.hpp"
#include "tuple/map.hpp"
#include "tuple/splits.hpp"
#include "tuple/zip_with.hpp"
#include "value_t.hpp"

namespace PP
{
PP_FUNCTOR(arg_splitter,
           concepts::type auto delimiter_type,
           concepts::tuple auto&& to_construct_types,
           concepts::value auto i,
           auto&&... args)
{
	auto splits = tuple_splits(
	    [delimiter_type](auto&& arg)
	    {
		    return value<~PP_DT(arg) == PP_COPY_TYPE(delimiter_type)>;
	    },
	    forward_as_tuple(PP_F(args)...));

	static_assert(tuple_type_count(PP_DT(to_construct_types)) ==
	                  tuple_type_count(PP_DT(splits)),
	              "arg_splitter: bad arg delimiter count");

	return (
	    *functor(
	        [](concepts::type auto to_construct_type, concepts::tuple auto args)
	        {
		        return [t = move(to_construct_type), as = move(args)]()
		        {
			        return (construct_pack * t)[move(as)];
		        };
	        }) +
	    (PP_F(to_construct_types) ^ move(splits)))[i]();
});
}
