#pragma once
#include <PP/add_cv.hpp>
#include <PP/get_cv.hpp>

namespace PP
{
PP_CIA copy_cv = [](concepts::type auto&& from, concepts::type auto&& to)
{
    return add_cv(get_cv_value_t(from), to);
};
}
