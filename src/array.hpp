#pragma once
template <typename T, size_t s>
struct array
{
	T data[s];
	
	T* begin()
	{
		return data;
	}
	const T* begin() const
	{
		return data;
	}
	T* end()
	{
		return data + s;
	}
	const T* end() const
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