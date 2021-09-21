#pragma once
#include "../declval.hpp"
#include "../functor.hpp"
#include "../get_type.hpp"

namespace PP
{
PP_FUNCTOR(is_convertible_to, concepts::type auto from, concepts::type auto to)
{
    return requires
    {
        [](PP_GT(to))
        {
        }(declval(from));
    };
});
}

namespace PP::concepts
{
template <typename From, typename To>
concept convertible_to = is_convertible_to(PP::type<From>, PP::type<To>);
}
