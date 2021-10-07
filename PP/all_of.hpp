#pragma once
#include "id.hpp"
#include "view.hpp"
#include <utility>

namespace PP
{
PP_FUNCTOR(all_of, concepts::view auto&& v, auto&& p = id_forward)
{
    for (auto&& e : PP_F(v))
        if (!PP_F(p)(e))
            return false;
    return true;
});
}
