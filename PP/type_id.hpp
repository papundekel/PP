#pragma once
#include <typeinfo>

#include "get_type.hpp"

namespace PP
{
PP_CIA type_id = [](concepts::type auto&& t) -> auto&
{
    return typeid(PP_GT(t));
};
}
