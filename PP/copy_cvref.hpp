#pragma once
#include <PP/copy_cv.hpp>
#include <PP/copy_reference.hpp>
#include <PP/remove_reference.hpp>

namespace PP
{
PP_CIA copy_cvref = [](concepts::type auto&& from, concepts::type auto&& to)
{
    return copy_reference(from, copy_cv(!from, to));
};
}
