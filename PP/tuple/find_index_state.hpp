#pragma once
#include <PP/size_t.hpp>

namespace PP::detail
{
struct tuple_find_index_state
{
    size_t index;
    bool found;
};
}