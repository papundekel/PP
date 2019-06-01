#include "floating.hpp"
#include "integral_signed.hpp"

template <typename T>
concept number_signed = integral_signed<T> || floating<T>;