#pragma once
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"

namespace PP
{
PP_CIA has_trivial_destructor = [](concepts::type auto&& t)
{
    return __has_trivial_destructor(PP_GT(t));
};

PP_CONCEPT0(with_trivial_destructor, has_trivial_destructor)
}
