#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"

#define PP_CONCEPT(concept_name, functor_name)                                 \
	namespace concepts                                                         \
	{                                                                          \
		template <typename T>                                                  \
		concept concept_name = ::PP::is_##functor_name(::PP::type<T>);         \
	}

#define PP_CONCEPT1(name) PP_CONCEPT(name, name)

#define PP_CONCEPT_FUNCTOR(concept_name, functor_name)                         \
	PP_FUNCTOR(is_##functor_name, ::PP::concepts::type auto t)                 \
	{                                                                          \
		return ::PP::concepts::concept_name<PP_GET_TYPE(t)>;                   \
	})

#define PP_CONCEPT_FUNCTOR1(name) PP_CONCEPT_FUNCTOR(name, name)
