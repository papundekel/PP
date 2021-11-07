#pragma once
#include "compose.hpp"
#include "cv_qualifier.hpp"
#include "decompose_pair.hpp"
#include "overloaded.hpp"
#include "to_type_t.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA decompose_volatile = compose(
    overloaded(
        []<typename T>(type_t<volatile T>)
        {
            return make_decompose_pair(type<T>,
                                       PP::value<cv_qualifier::Volatile>);
        },
        []<typename T>(type_t<T>)
        {
            return make_decompose_pair(type<T>, PP::value<cv_qualifier::none>);
        }),
    to_type_t);
}
