#pragma once
#include <PP/macros/simple_concept.hpp>
#include <PP/concepts/same_except_cv.hpp>

namespace PP
{
namespace concepts
{
template <typename T>
concept void_type = same_except_cv<T, void>;

template <typename T>
concept null = same_except_cv<T, decltype(nullptr)>;

template <typename T>
concept float_type = same_except_cv<T, float>;

template <typename T>
concept double_type = same_except_cv<T, double>;

template <typename T>
concept long_double = same_except_cv<T, long double>;

template <typename T>
concept bool_type = same_except_cv<T, bool>;

template <typename T>
concept char_type = same_except_cv<T, char>;

template <typename T>
concept signed_char = same_except_cv<T, signed char>;

template <typename T>
concept unsigned_char = same_except_cv<T, unsigned char>;

template <typename T>
concept wchar = same_except_cv<T, wchar_t>;

#ifdef __cpp_char8_t
template <typename T>
concept char8 = same_except_cv<T, char8_t>;
#endif

#ifdef __cpp_unicode_characters
template <typename T>
concept char16 = same_except_cv<T, char16_t>;

template <typename T>
concept char32 = same_except_cv<T, char32_t>;
#endif

template <typename T>
concept signed_short = same_except_cv<T, signed short int>;

template <typename T>
concept signed_int = same_except_cv<T, signed int>;

template <typename T>
concept signed_long = same_except_cv<T, signed long int>;

template <typename T>
concept signed_long_long = same_except_cv<T, signed long long int>;

template <typename T>
concept unsigned_short = same_except_cv<T, unsigned short int>;

template <typename T>
concept unsigned_int = same_except_cv<T, unsigned int>;

template <typename T>
concept unsigned_long = same_except_cv<T, unsigned long int>;

template <typename T>
concept unsigned_long_long = same_except_cv<T, unsigned long long int>;
}

PP_CONCEPT_FUNCTOR(void_type, void);
PP_CONCEPT_FUNCTOR1(null);
PP_CONCEPT_FUNCTOR(float_type, float);
PP_CONCEPT_FUNCTOR(double_type, double);
PP_CONCEPT_FUNCTOR1(long_double);
PP_CONCEPT_FUNCTOR(bool_type, bool);
PP_CONCEPT_FUNCTOR(char_type, char);
PP_CONCEPT_FUNCTOR1(signed_char);
PP_CONCEPT_FUNCTOR1(unsigned_char);
PP_CONCEPT_FUNCTOR1(wchar);
#ifdef __cpp_char8_t
PP_CONCEPT_FUNCTOR1(char8);
#endif
#ifdef __cpp_unicode_characters
PP_CONCEPT_FUNCTOR1(char16);
PP_CONCEPT_FUNCTOR1(char32);
#endif
PP_CONCEPT_FUNCTOR1(signed_short);
PP_CONCEPT_FUNCTOR1(signed_int);
PP_CONCEPT_FUNCTOR1(signed_long);
PP_CONCEPT_FUNCTOR1(signed_long_long);
PP_CONCEPT_FUNCTOR1(unsigned_short);
PP_CONCEPT_FUNCTOR1(unsigned_int);
PP_CONCEPT_FUNCTOR1(unsigned_long);
PP_CONCEPT_FUNCTOR1(unsigned_long_long);
}
