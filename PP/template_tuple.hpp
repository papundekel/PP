#pragma once
#include <tuple>
#include "template_t.hpp"

namespace PP
{
	template <template <typename...> typename... Templates>
	constexpr inline auto template_tuple = std::tuple<template_t<Templates>...>{};
}
