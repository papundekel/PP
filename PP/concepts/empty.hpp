#pragma once
#include "../apply_partially.hpp"
#include "../apply_template.hpp"
#include "../functor.hpp"
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"
#include "../size_of.hpp"
#include "../template_t.hpp"
#include "non_union_class.hpp"

namespace PP::detail
{
template <typename T, typename Base>
struct empty_helper
    : public Base
{
    T t;
};

namespace functors
{
PP_CIA is_empty_helper = [](concepts::type auto member_t, concepts::type auto t)
{
    if constexpr (is_non_union_class(PP_COPY_TYPE(t)))
        return size_of(Template<empty_helper>(member_t, t)) ==
               size_of(member_t);
    else
        return false;
};
}
PP_FUNCTOR(is_empty_helper)
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
