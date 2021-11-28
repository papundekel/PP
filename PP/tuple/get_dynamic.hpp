#pragma once
#include <PP/size_t.hpp>
#include <PP/view/concept.hpp>
#include <PP/view/concept.hpp>

namespace PP::tuple
{
PP_CIA get_dynamic = [](size_t i, concepts::tuple auto&& tuple)
{
    return view::begin_(make_tuple_view(PP_F(tuple)))[i];
};
}
