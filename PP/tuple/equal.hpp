#pragma once
#include "concept.hpp"
#include "count.hpp"
#include "zip_with.hpp"

constexpr auto operator==(const PP::concepts::tuple auto& a,
                          const PP::concepts::tuple auto& b)
{
    return PP::tuple::count(a) == PP::tuple::count(b) &&
           PP::tuple::all(PP::eql, a ^ b);
}
