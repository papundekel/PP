#pragma once
#include "value_t.hpp"

template <typename T, template <typename> typename Test>
constexpr auto not_v = !Test<T>::value;
template <typename T, template <typename> typename Test>
struct not_s : value_t<not_v<T, Test>> {};
template <typename T, template <typename> typename Test>
concept not_c = not_v<T, Test>;