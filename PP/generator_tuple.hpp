#pragma once
#include <PP/get_value.hpp>
#include <PP/id.hpp>
#include <PP/type_t.hpp>

namespace PP
{
template <auto generator, size_t count>
class generator_tuple_t
{
public:
    constexpr decltype(auto) operator[](concepts::value auto&& i) const noexcept
    {
        return generator(i);
    }

    constexpr auto tuple_count() const noexcept
    {
        return value<count>;
    }

    constexpr auto element(concepts::value auto&& i) const noexcept
    {
        return PP_DT(generator(i));
    }
};

PP_CIA make_id_tuple = [](concepts::value auto&& count)
{
    return generator_tuple_t<id_copy, PP_GV(count)>{};
};
}
