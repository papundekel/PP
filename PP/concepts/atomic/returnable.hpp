#pragma once
#include "../../functor.hpp"
#include "../../get_type.hpp"

namespace PP::detail
{
template <typename T>
T templated_return_dummy_function(type_t<T>);
}

namespace PP
{
namespace functors
{
PP_CIA is_returnable = [](concepts::type auto t)
{
    return requires
    {
        detail::templated_return_dummy_function(to_type_t(t));
    };
};
}
PP_FUNCTOR(is_returnable)
}
