#pragma once
#include "apply_partially_first.hpp"
#include "apply_template_pack.hpp"
#include "compose.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "tuple/apply.hpp"
#include "tuple/concept.hpp"
#include "tuple/get.hpp"

namespace PP
{
PP_CIA apply_template = [](auto Template, concepts::tuple auto&& types)
{
    return tuple::apply(apply_template_pack * Template, PP_F(types));
};

PP_CIA apply_template_type = compose(get_type, apply_template);
PP_CIA apply_template_value = compose(get_type_value, apply_template);
}

template <template <typename...> typename Template>
constexpr auto PP::template_t<Template>::operator[](auto&& types) const noexcept
{
    return apply_template(*this, PP_F(types));
}
