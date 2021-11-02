#pragma once
#include "construct_pack.hpp"
#include "make_in_place_index.hpp"

#include <variant>

namespace PP
{
PP_CIA make_variant_pack =
    [](concepts::type auto&& t, concepts::value auto&& i, auto&&... args)
{
    return construct_pack(t, make_in_place_index(i), PP_F(args)...);
};
}
