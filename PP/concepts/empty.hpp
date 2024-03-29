#pragma once
#include <PP/get_type.hpp>
#include <PP/macros/simple_concept.hpp>
#include <PP/pack/apply_template.hpp>
#include <PP/partial.hpp>
#include <PP/size_of.hpp>
#include <PP/template_t.hpp>
#include <PP/concepts/non_union_class.hpp>

namespace PP::detail
{
template <typename T, typename Base>
struct empty_helper : public Base
{
    T t;
};

PP_CIA is_empty_helper =
    [](concepts::type auto&& member_t, concepts::type auto&& t)
{
    if constexpr (is_non_union_class(PP_CT(t)))
        return size_of(Template<empty_helper>(member_t, t)) ==
               size_of(member_t);
    else
        return false;
};
}

namespace PP
{
PP_CIA is_empty = detail::is_empty_helper * type_char;
}

namespace PP::concepts
{
template <typename T>
concept empty = is_empty(PP::type<T>) && non_union_class<T>;
}
