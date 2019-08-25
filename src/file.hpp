#pragma once
#include <fstream>

template <typename T>
void save(const char* name, const T* buffer, size_t size)
{
	std::ofstream file(name);
	file.clear();
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	file.write(reinterpret_cast<const char*>(buffer), size * sizeof(T));
	file.close();
}
template <typename T>
void load(const char* name, T* buffer)
{
	std::ifstream file(name);
	size_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	file.read(reinterpret_cast<char*>(buffer), size * sizeof(T));
	file.close();
}