#pragma once
#include <PP/array_vector.hpp>
#include <PP/ostream_basic.hpp>
#include <PP/size_t.hpp>

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
