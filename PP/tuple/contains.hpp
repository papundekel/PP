#pragma once
#include <PP/tuple/count.hpp>
#include <PP/find_dynamic.hpp>

namespace PP::tuple
{
PP_CIA contains = [](auto&& predicate, concepts::tuple auto&& t)
{
    return find_dynamic(PP_F(predicate), PP_F(t)) != count(PP_F(t));
};
}
