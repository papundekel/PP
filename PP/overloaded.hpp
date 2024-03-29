#pragma once

namespace PP
{
template <typename... Ts>
struct overloaded : public Ts...
{
    using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
}
