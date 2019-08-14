#pragma once
#include "type_t.hpp"
#define template_remove_is template <typename T, template <typename> typename F>
template_remove_is
struct remove_s : type_t<T> {};
template_remove_is
struct remove_s<F<T>> : type_t<T> {};
template_remove_is
using remove_t = remove_s<T, F>::type;