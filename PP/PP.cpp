#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include "any_of.hpp"
#include "transform_view.hpp"
#include "zip_with.hpp"
#include "copy.hpp"
#include "move.hpp"
#include "simple_vector.hpp"
#include "get_value_from_key.hpp"
#include "same_type.hpp"
#include "type_t.hpp"
#include "overloaded.hpp"
#include "reference_wrapper.hpp"
#include "any_iterator.hpp"
#include "map_v.hpp"
#include "add_cv.hpp"
#include "same_type.hpp"
#include "tuple_zip.hpp"
#include "type_tuple.hpp"
#include "get_value_from_key.hpp"
#include "sizeof_v.hpp"
#include "tuple_equal.hpp"
#include "tuple_like.hpp"
#include "tuple_filter.hpp"
#include "tuple_map.hpp"
#include "disjunction.hpp"
#include "template_tuple.hpp"
#include "ref_qualifier.hpp"
#include "tuple_for_each.hpp"
#include "get_function_info.hpp"
#include "functional/compose.hpp"
#include "make_function_type.hpp"
#include "value_wrapper.hpp"

constexpr inline auto get_unqualified_function =
	PP::make_function_type
	||
	PP::value_wrapper <
		[]<typename Return, typename... Parameters>(PP::function_info<Return, Parameters...>)
		{
			return PP::function_info(PP::type_v<Return(Parameters...)>);
		} || PP::get_function_info > ;


int main()
{
	auto x = PP::make_function_type(PP::type_v<int>, PP::type_tuple_v<char, char>);
	auto y = PP::type_v<int(char, char)>;
	std::cout << (x == y);

	auto z = get_unqualified_function(x);
	std::cout << (z == y);

	std::cout.flush();
	return 0;
}
