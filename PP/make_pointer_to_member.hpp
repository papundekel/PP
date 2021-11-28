#pragma once
#include <PP/get_type.hpp>
#include <PP/type_t.hpp>

namespace PP
{
PP_CIA make_pointer_to_member =
    [](concepts::type auto&& Class, concepts::type auto&& t)
{
    return type<PP_GT(t) PP_GT(Class)::*>;
};
}
