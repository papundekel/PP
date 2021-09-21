#pragma once
#include "../functor.hpp"
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"

namespace PP
{
PP_FUNCTOR(has_trivial_destructor, concepts::type auto t)
{
    return __has_trivial_destructor(PP_GT(t));
});

PP_CONCEPT0(with_trivial_destructor, has_trivial_destructor)
}
