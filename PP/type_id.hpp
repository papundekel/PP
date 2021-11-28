#pragma once
#include <PP/get_type.hpp>

#include <typeinfo>

namespace PP
{
PP_CIA type_id = [](concepts::type auto&& t) -> auto&
{
    return typeid(PP_GT(t));
};
}
