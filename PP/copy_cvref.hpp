#pragma once
#include "copy_cv.hpp"
#include "copy_reference.hpp"
#include "remove_reference.hpp"

namespace PP
{
PP_CIA copy_cvref = [](concepts::type auto&& from, concepts::type auto&& to)
{
    return copy_reference(from, copy_cv(!from, to));
};
}
