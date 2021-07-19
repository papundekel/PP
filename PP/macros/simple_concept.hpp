#pragma once
#include "../functor.hpp"
#include "../get_type.hpp"

#define PP_CONCEPT0(concept_name, functor_name_full)                           \
	namespace concepts                                                         \
	{                                                                          \
		template <typename T>                                                  \
		concept concept_name = ::PP::functor_name_full(::PP::type<T>);         \
	}

#define PP_CONCEPT(concept_name, functor_name)                                 \
	PP_CONCEPT0(concept_name, is_##functor_name)

#define PP_CONCEPT1(name) PP_CONCEPT(name, name)

#define PP_CONCEPT_FUNCTOR(concept_name, functor_name)                         \
	PP_FUNCTOR(is_##functor_name, ::PP::concepts::type auto t)                 \
	{                                                                          \
		return ::PP::concepts::concept_name<PP_GT(t)>;                         \
	})

#define PP_CONCEPT_FUNCTOR1(name) PP_CONCEPT_FUNCTOR(name, name)
