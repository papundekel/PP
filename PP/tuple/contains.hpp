#pragma once
#include "../functor.hpp"
#include "count.hpp"
#include "find_dynamic.hpp"

namespace PP::tuple
{
PP_FUNCTOR(contains, auto&& predicate, concepts::tuple auto&& t)
{
    return find_dynamic(PP_F(predicate), PP_F(t)) != count(PP_F(t));
});
}
