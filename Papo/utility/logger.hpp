#pragma once
#include <string>
#include "int.hpp"

namespace
{
	constexpr auto x = (8 * sizeof(size_t) - 2) / 2;
}

struct logger
{
	enum ct {
		def,
		cop,
		mov
	};

	static size_t count;

	size_t constructor : 2;
	size_t origin : x;
	size_t index : x;

	logger();
	logger(const logger&);
	logger(logger&&) noexcept;
	logger& operator=(const logger&);
	logger& operator=(logger&&);
	~logger();
};