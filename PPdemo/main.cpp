#include <iostream>
#include <vector>

#include "PP/cv_decomposition.hpp"
#include "PP/promotion_type.hpp"
#include "PP/value_sequence.hpp"
#include "PP/view_remove.hpp"
#include "PP/simple_vector.hpp"

[[maybe_unused]]
std::ostream& print_cv(PP::cv_decomposition_element e, std::ostream& out)
{
	switch (e.cv)
	{
	case PP::cv_qualifier::none:
		out << "none";				break;
	case PP::cv_qualifier::Const:
		out << "const";				break;
	case PP::cv_qualifier::Volatile:
		out << "volatile";			break;
	case PP::cv_qualifier::const_volatile:
		out << "const volatile";	break;
	}

	out << " ";

	switch (e.type)
	{
	case PP::cv_decomposition_type::pointer:
		out << "p";				break;
	case PP::cv_decomposition_type::pointer_to_member:
		out << "pm";				break;
	case PP::cv_decomposition_type::array_known:
		out << "ak";			break;
	case PP::cv_decomposition_type::array_unknown:
		out << "au";	break;
	case PP::cv_decomposition_type::none:
		out << "none";	break;
	}

	return out << " " << e.extent;
}

int main()
{
	

	std::cout.flush();
	return 0;
}
