#pragma once
#include <PP/compose.hpp>
#include <PP/decompose_pair.hpp>
#include <PP/overloaded.hpp>
#include <PP/ref_qualifier.hpp>
#include <PP/to_type_t.hpp>

namespace PP
{
PP_CIA decompose_reference = compose(
    overloaded(
        []<typename T>(type_t<T&&>)
        {
            return make_decompose_pair(type<T>,
                                       PP::value<ref_qualifier::rvalue>);
        },
        []<typename T>(type_t<T&>)
        {
            return make_decompose_pair(type<T>,
                                       PP::value<ref_qualifier::lvalue>);
        },
        []<typename T>(type_t<T>)
        {
            return make_decompose_pair(type<T>, PP::value<ref_qualifier::none>);
        }),
    to_type_t);
}
