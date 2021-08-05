#include <iostream>

#include "PP/add_const.hpp"
#include "PP/applier.hpp"
#include "PP/apply_partially.hpp"
#include "PP/apply_partially_first.hpp"
#include "PP/concepts/integer.hpp"
#include "PP/concepts/same_except_cvref.hpp"
#include "PP/construct_pack.hpp"
#include "PP/containers/tuple.hpp"
#include "PP/containers/tuple_std.hpp"
#include "PP/containers/type_tuple.hpp"
#include "PP/copy_cvref.hpp"
#include "PP/decay.hpp"
#include "PP/declval.hpp"
#include "PP/decompose_template.hpp"
#include "PP/forward_wrap.hpp"
#include "PP/functor.hpp"
#include "PP/get_std.hpp"
#include "PP/get_type.hpp"
#include "PP/get_value.hpp"
#include "PP/init_type.hpp"
#include "PP/macros/simple_concept.hpp"
#include "PP/operators.hpp"
#include "PP/placeholder.hpp"
#include "PP/shift_view.hpp"
#include "PP/simple_view.hpp"
#include "PP/size_t.hpp"
#include "PP/tuple/all.hpp"
#include "PP/tuple/any.hpp"
#include "PP/tuple/apply.hpp"
#include "PP/tuple/concept.hpp"
#include "PP/tuple/count.hpp"
#include "PP/tuple/element.hpp"
#include "PP/tuple/empty.hpp"
#include "PP/tuple/for_each.hpp"
#include "PP/tuple/get.hpp"
#include "PP/tuple/make.hpp"
#include "PP/tuple/map.hpp"
#include "PP/tuple/prepend.hpp"
#include "PP/tuple/types.hpp"
#include "PP/tuple/value_sequence_for.hpp"
#include "PP/value_sequence.hpp"
#include "PP/value_t.hpp"

#include "PP/tuple/split.hpp"

//#include "PP/tuple/zip_with.hpp"
//#include "PP/view/concept.hpp"
//#include "PP/view/zip.hpp"
//#include "PP/zip_iterator_std.hpp"
//#include "PP/view/first_equal.hpp"

int main()
{
	int a, b, c;
	// auto x = PP::tuple::splitter(a, b, c);

	return 0;
}
