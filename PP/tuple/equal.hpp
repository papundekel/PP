#pragma once
#include <PP/tuple/concept.hpp>
#include <PP/tuple/count.hpp>
#include <PP/tuple/zip_with.hpp>

constexpr auto operator==(const PP::concepts::tuple auto& a,
                          const PP::concepts::tuple auto& b)
{
    return PP::tuple::count(a) == PP::tuple::count(b) &&
           PP::tuple::all(PP::eql, a ^ b);
}
