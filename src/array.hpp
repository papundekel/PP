#pragma once
template <typename T, size_t s>
struct array
{
	T data[s];
	
	constexpr T* begin()
	{
		return data;
	}
	constexpr const T* begin() const
	{
		return data;
	}
	constexpr T* end()
	{
		return data + s;
	}
	constexpr const T* end() const
	{
		return data + s;
	}
	constexpr auto size()
	{
		return s;
	}
};

template <class T, class... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;