#pragma once

constexpr auto transform_same = [](auto transform)
{
    return [transform](auto x)
    {
        return same(transform(x))(x);
    };
};