#pragma once
#include "../apply_partially.hpp"
#include "../compose_many.hpp"
#include "../get_reference.hpp"
#include "../macros/simple_concept.hpp"
#include "../operators.hpp"

namespace PP
{
PP_CIA is_lvalue_reference =
    compose_many(eql * ref_qualifier::lvalue, get_value,
            get_reference_value_t);

PP_CONCEPT1(lvalue_reference)
}
