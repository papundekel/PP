#pragma once
#include <PP/PP/compose.hpp>
#include <PP/PP/construct_pack.hpp>
#include <PP/PP/containers/type_tuple.hpp>
#include <PP/PP/decl_type.hpp>
#include <PP/PP/overloaded.hpp>
#include <PP/PP/tuple/make.hpp>
#include <PP/PP/tuple/prepend.hpp>

namespace PP
{
namespace detail
{
constexpr auto promotion_type_convertor(int x)
{
    return x;
}
constexpr auto promotion_type_convertor(unsigned int x)
{
    return x;
}
constexpr auto promotion_type_convertor(long x)
{
    return x;
}
constexpr auto promotion_type_convertor(unsigned long x)
{
    return x;
}
constexpr auto promotion_type_convertor(long long x)
{
    return x;
}
constexpr auto promotion_type_convertor(unsigned long long x)
{
    return x;
}
constexpr auto promotion_type_convertor(double x)
{
    return x;
}
constexpr auto promotion_type_convertor(long double x)
{
    return x;
}
}

PP_CIA has_implicit_conversion_to_arithmetic_type = [](concepts::type auto&& t)
{
    return requires(PP_GT(t) x)
    {
        promotion_type_convertor(x);
    };
};

PP_CIA promotion_type = compose_many(
    decl_type_copy,
    [](auto x)
    {
        return detail::promotion_type_convertor(x);
    },
    construct_pack);
}
