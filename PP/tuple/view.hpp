#pragma once
#include "../apply_template.hpp"
#include "../make_variant_pack.hpp"
#include "../wrap_reference.hpp"
#include "concept.hpp"
#include "get_types.hpp"
#include "map_to_array.hpp"
#include "zip_indices.hpp"

namespace PP::tuple
{
PP_FUNCTOR(make_view, concepts::tuple auto&& tuple)
{
    return *(make_variant_pack *
             Template<std::variant>[wrap_reference + get_types(PP_F(tuple))]) <
           zip_indices(PP_F(tuple));
});
}
