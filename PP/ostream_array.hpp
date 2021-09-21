#pragma once
#include "array_vector.hpp"
#include "ostream_basic.hpp"
#include "size_t.hpp"

namespace PP
{
namespace detail
{
template <size_t count>
struct ostream_array_helper
{
    template <typename T>
    using help = array_vector<T, count, true>;
};
}

template <size_t count>
using ostream_array =
    detail::ostream_basic<detail::ostream_array_helper<count>::template help>;
}
