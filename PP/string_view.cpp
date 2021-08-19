#include "string_view.hpp"

#include <iostream>

std::ostream& PP::operator<<(std::ostream& out, PP::string_view sv)
{
	return out.write(PP::view::begin(sv), PP::view::count(sv));
}
