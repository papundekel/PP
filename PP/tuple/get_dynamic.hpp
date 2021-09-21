#pragma once
#include "../size_t.hpp"
#include "../view/concept.hpp"
#include "view.hpp"

namespace PP::tuple
{
PP_FUNCTOR(get_dynamic, size_t i, concepts::tuple auto&& tuple)
{
    return view::begin(make_tuple_view(PP_F(tuple)))[i];
});
}
