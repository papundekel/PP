#pragma once
#include <PP/pack/apply_template.hpp>
#include <PP/template_t.hpp>

namespace PP::detail
{
template <typename T>
using add_const_t = const T;
}

namespace PP
{
PP_CIA add_const = Template<detail::add_const_t>;
}
