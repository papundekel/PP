#pragma once
#include "value_t.hpp"

template <typename T, template <typename> typename Test>
constexpr auto is_not_v = !Test<T>::value;
template <typename T, template <typename> typename Test>
struct is_not : value_t<is_not_v<T, Test>> {};
template <typename T, template <typename> typename Test>
concept non = is_not_v<T, Test>;