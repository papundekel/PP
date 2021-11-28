#pragma once
#include <PP/compose_apply.hpp>
#include <PP/containers/tuple.hpp>
#include <PP/generator_tuple.hpp>
#include <PP/tuple/count.hpp>
#include <PP/zip_with.hpp>

namespace PP::tuple
{
PP_CIA zip_indices = [](concepts::tuple auto&& t)
{
    return [](auto i, auto&& element)
    {
        return container<decltype(i), decltype(element)>(placeholder,
                                                         i,
                                                         PP_F(element));
    } +++(make_id_tuple(count_value_t(t)) ^ PP_F(t));
};
}
