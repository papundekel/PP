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
	PP::simple_vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);

	a.erase_until_end(PP::view_remove([]
		(int a)
		{
			return a % 2 == 0;
		}, a));

	for (int x : a)
		std::cout << x << '\n';

	std::cout.flush();
	return 0;
}
