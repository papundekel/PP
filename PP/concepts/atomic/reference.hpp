#pragma once
#include "../../add_reference.hpp"
#include "../../conjunction.hpp"
#include "../same.hpp"
#include "referencable.hpp"

namespace PP::detail::functors
{
PP_CIA is_reference_helper = [](concepts::type auto t)
{
    return t + add_rvalue_tag == t;
};
}

namespace PP
{
PP_CIA is_reference = is_referencable && detail::functors::is_reference_helper;
}
