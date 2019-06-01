#include "same.hpp"
#include "decay.hpp"

template <typename T, typename U>
concept almost = same<T, decay<U>>;