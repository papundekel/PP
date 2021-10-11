#pragma once
#include "view/pair.hpp"

namespace PP
{
PP_CIA make_singular_view = [](auto& object)
{
    return simple_view(&object, &object + 1);
};
}
