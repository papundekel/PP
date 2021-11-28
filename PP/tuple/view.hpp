#pragma once
#include <PP/apply_template.hpp>
#include <PP/make_variant_pack.hpp>
#include <PP/wrap_reference.hpp>
#include <PP/tuple/concept.hpp>
#include <PP/get_types.hpp>
#include <PP/map_to_array.hpp>
#include <PP/zip_indices.hpp>

namespace PP::tuple
{
PP_CIA make_view = [](concepts::tuple auto&& tuple)
{
    return *(make_variant_pack *
             Template<std::variant>[wrap_reference + get_types(PP_F(tuple))]) <
           zip_indices(PP_F(tuple));
};
}
