#pragma once
#include "type_tuple.hpp"

namespace PP
{
PP_CIA character_types = type_tuple<char,
                                    signed char,
                                    unsigned char,
                                    wchar_t
#ifdef __cpp_char8_t
                                    ,
                                    char8_t
#endif
#ifdef __cpp_unicode_characters
                                    ,
                                    char16_t,
                                    char32_t
#endif
                                    >;

PP_CIA signed_integer_types =
    type_tuple<short int, int, long int, long long int>;

PP_CIA unsigned_integer_types = type_tuple<unsigned short int,
                                           unsigned int,
                                           unsigned long int,
                                           unsigned long long int>;

PP_CIA floating_point_types = type_tuple<float, double, long double>;

PP_CIA integer_types =
    type_tuple_concat(signed_integer_types, unsigned_integer_types);

PP_CIA integral_types =
    type_tuple_concat(type_tuple<bool>,
                      type_tuple_concat(character_types, integer_types));

PP_CIA arithmetic_types =
    type_tuple_concat(floating_point_types, integral_types);

PP_CIA non_void_fundamental_types =
    type_tuple_concat(type_tuple<decltype(nullptr)>, arithmetic_types);

PP_CIA fundamental_types =
    type_tuple_concat(type_tuple<void>, non_void_fundamental_types);
}
