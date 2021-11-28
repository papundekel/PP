#pragma once
#include <PP/compose_many.hpp>
#include <PP/get_reference.hpp>
#include <PP/macros/simple_concept.hpp>
#include <PP/operators.hpp>
#include <PP/partial.hpp>

namespace PP
{
PP_CIA is_lvalue_reference =
    compose_many(eql * ref_qualifier::lvalue, get_value, get_reference_value_t);

PP_CONCEPT1(lvalue_reference)
}
