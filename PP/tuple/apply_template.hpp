#pragma once
#include <PP/combine.hpp>
#include <PP/compose.hpp>
#include <PP/get_type.hpp>
#include <PP/get_value.hpp>
#include <PP/pack/apply_template.hpp>
#include <PP/pack/get.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/apply.hpp>
#include <PP/tuple/concept.hpp>

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
