#pragma once
#include "get_type.hpp"
#include "type_t.hpp"

namespace PP
{
PP_CIA construct_pack = [](concepts::type auto&& t,
                           auto&&... args) -> decltype(auto)
{
    return PP_GT(t)(PP_F(args)...);
};
}

template <typename T>
constexpr decltype(auto) PP::type_t<T>::operator()(auto&&... args) const
{
    return construct_pack(*this, PP_F(args)...);
}
