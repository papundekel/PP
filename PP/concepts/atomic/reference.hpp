#pragma once
#include <PP/add_reference.hpp>
#include <PP/conjunction.hpp>
#include <PP/same.hpp>
#include <PP/concepts/atomic/referencable.hpp>

namespace PP::detail
{
PP_CIA is_reference_helper = [](concepts::type auto&& t)
{
    return t + add_rvalue_tag == t;
};
}

namespace PP
{
PP_CIA is_reference = is_referencable && detail::is_reference_helper;
}
