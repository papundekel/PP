#pragma once
#include "add_cv.hpp"
#include "add_reference.hpp"

namespace PP
{
PP_FUNCTOR(add_cv_ref,
           concepts::value auto cv,
           concepts::value auto ref,
           concepts::type auto t)
{
    return add_reference(ref, add_cv(cv, t));
});
}
