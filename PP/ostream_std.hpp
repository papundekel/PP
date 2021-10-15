#pragma once
#include "ostream.hpp"

namespace PP
{
template <typename Char>
class ostream_basic_std final : public ostream_basic<Char>
{
    std::basic_ostream<Char>& out;

public:
    constexpr ostream_basic_std(std::basic_ostream<Char>& out) noexcept
        : out(out)
    {}

    void write(Char c) noexcept override final
    {
        out.put(c);
    }
};

using ostream_std = ostream_basic_std<char>;
}
