#pragma once
#include <PP/get_value.hpp>

#include <variant>

namespace PP
{
PP_CIA make_in_place_index = [](concepts::value auto&& i)
{
    return std::in_place_index<PP_GV(i)>;
};
}
