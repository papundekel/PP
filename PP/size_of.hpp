#pragma once
#include "get_type.hpp"

namespace PP
{
PP_FUNCTOR(size_of, concepts::type auto t)
{
    return sizeof(PP_GT(t));
});
}
