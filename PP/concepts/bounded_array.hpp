#pragma once
#include "../macros/simple_concept.hpp"
#include "../overloaded.hpp"
#include "../size_t.hpp"
#include "../to_type_t.hpp"

namespace PP
{
PP_CIA is_bounded_array = compose(overloaded(
                                      []<typename T, size_t N>(type_t<T[N]>)
                                      {
                                          return true;
                                      },
                                      [](auto)
                                      {
                                          return false;
                                      }),
                                  to_type_t);

PP_CONCEPT1(bounded_array)
}
