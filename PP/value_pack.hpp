#pragma once
#include "type_pack.h"
#include "value_t.h"

template <auto... Values>
using value_pack = type_pack<value_t<Values>...>;
