#include "declval.hpp"

template <typename T>
constexpr auto _decay()
{
    return declval<T>();
}

template <typename T>
using decay = decltype(_decay<T>());