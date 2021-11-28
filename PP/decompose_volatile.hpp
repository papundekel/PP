#pragma once
#include <PP/compose.hpp>
#include <PP/cv_qualifier.hpp>
#include <PP/decompose_pair.hpp>
#include <PP/overloaded.hpp>
#include <PP/to_type_t.hpp>
#include <PP/value_t.hpp>

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
