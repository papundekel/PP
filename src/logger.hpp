#pragma once

struct logger
{
	logger();
	logger(const logger&);
	logger(logger&&) noexcept;
	logger& operator=(const logger&);
	logger& operator=(logger&&);
	~logger();
};