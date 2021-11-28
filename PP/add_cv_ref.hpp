#pragma once
#include <PP/add_cv.hpp>
#include <PP/add_reference.hpp>

namespace PP
{
PP_CIA add_cv_ref = [](concepts::value auto&& cv,
                       concepts::value auto&& ref,
                       concepts::type auto&& t)
{
    return add_reference * PP_FW(ref) <<= add_cv * PP_FW(cv) <<= PP_F(t);
};
}
