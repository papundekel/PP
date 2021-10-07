#include "string_view.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& out, PP::string_view sv)
{
    [[maybe_unused]] auto x = PP::view::end(sv);
    return out.write(PP::view::begin(sv), PP::view::count(sv));
}
