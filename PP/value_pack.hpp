#pragma once
#include "type_pack.hpp"
#include "value_t.hpp"

namespace PP
{
	template <auto... Values>
	using value_pack = type_pack<value_t<Values>...>;
}
