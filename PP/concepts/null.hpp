#pragma once
#include "../macros/simple_concept.hpp"
#include "same.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept null =
			same<T, 			   decltype(nullptr)> ||
			same<T, const 		   decltype(nullptr)> ||
			same<T, 	  volatile decltype(nullptr)> ||
			same<T, const volatile decltype(nullptr)>;
	}

	PP_CONCEPT_FUNCTOR(null)
}
