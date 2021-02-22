#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"

#define PP_CONCEPT(concept_name, functor_name)								   \
	namespace concepts														   \
	{																		   \
		template <typename T>												   \
		concept concept_name = ::PP::is_##functor_name(::PP::type<T>);		   \
	}

#define PP_CONCEPT1(name) PP_CONCEPT(name, name)

#define PP_CONCEPT_FUNCTOR(name)											   \
	PP_FUNCTOR(is_##name, ::PP::concepts::type auto t)						   \
	{																		   \
		return ::PP::concepts::name<PP_GET_TYPE(t)>;						   \
	});
