#pragma once
#include <ostream>

#include "ostream.hpp"
#include "view.hpp"

namespace PP::detail
{
template <template <typename> typename Buffer>
class ostream_basic final : public ostream
{
    Buffer<char> buffer;

public:
    constexpr void write(char c) noexcept override final
    {
        buffer.push_back(c);
    }
};
}
