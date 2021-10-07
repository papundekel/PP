#pragma once
#include "concept.hpp"
#include "count.hpp"
#include "zip_with.hpp"

constexpr auto operator==(const PP::concepts::tuple auto& a,
                          const PP::concepts::tuple auto& b)
{
    return PP::tuple::count(a) == PP::tuple::count(b) && tuple_all(eql, a ^ b);
}
