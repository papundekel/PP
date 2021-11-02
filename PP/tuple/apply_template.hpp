#pragma once
#include "../combine.hpp"
#include "../compose.hpp"
#include "../get_type.hpp"
#include "../get_value.hpp"
#include "../pack/apply_template.hpp"
#include "../pack/get.hpp"
#include "../partial_.hpp"
#include "apply.hpp"
#include "concept.hpp"

namespace PP::tuple
{
PP_CIA apply_template =
    combine(apply,
            compose(partial_first* pack::apply_template, pack::get_0),
            pack::get_1);

PP_CIA apply_template_type = compose(get_type, apply_template);
PP_CIA apply_template_value = compose(get_type_value, apply_template);
}

template <template <typename...> typename Template>
constexpr auto PP::template_t<Template>::operator[](auto&& types) const noexcept
{
    return PP::tuple::apply_template(*this, PP_F(types));
}
