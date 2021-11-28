#pragma once
#include <PP/id.hpp>
#include <PP/view/concept.hpp>

#include <utility>

namespace PP
{
PP_CIA all_of = [](concepts::view auto&& v, auto&& p = id_forward)
{
    for (auto&& e : PP_F(v))
        if (!PP_F(p)(e))
            return false;
    return true;
};
}
