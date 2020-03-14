#pragma once

constexpr auto negation = [](auto x)
{
    return [](auto y)
    {
        return !x(y);
    };
};