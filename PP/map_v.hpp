#pragma once
#include "type_t.hpp"
#include "template_t.hpp"
#include "get_value.hpp"

namespace PP
{
	constexpr inline auto map_v =
		[]<template <typename> typename Template, typename Type>(template_t<Template>, type_t<Type>) -> decltype(auto)
		{
			return get_value<Template<Type>>();
		};
}
