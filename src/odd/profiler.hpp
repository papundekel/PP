#pragma once
#include <chrono>

template <typename function, typename... Args>
auto profile(function F, int count, Args&&... args)
{
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; i++)
	{
		F(std::forward<Args>(args)...);
	}
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin).count();
}

template <typename T, typename function, typename... Args>
auto profile(const T& object, function F, int count, Args&&... args)
{
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; ++i)
	{
		(object.*F)(std::forward<Args>(args)...);
	}
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin).count();
}