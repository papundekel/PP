#pragma once
#include "ostream.hpp"

namespace PP
{
class ostream_std final : public ostream
{
    std::ostream& out;

public:
    constexpr ostream_std(std::ostream& out) noexcept
        : out(out)
    {}

    void write(char c) noexcept override final;
};
}
