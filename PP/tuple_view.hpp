#pragma once
#include "apply_template.hpp"
#include "make_variant_pack.hpp"
#include "tuple_concept.hpp"
#include "tuple_get_types.hpp"
#include "tuple_map_to_array.hpp"
#include "tuple_zip_indices.hpp"
#include "wrap_reference.hpp"

namespace PP
{
	PP_FUNCTOR(make_tuple_view, concepts::tuple auto&& tuple)
	{
		return *(make_variant_pack *
		         Template<std::variant>[wrap_reference +
		                                tuple_get_types(PP_F(tuple))]) <
		       tuple_zip_indices(PP_F(tuple));
	});
}
