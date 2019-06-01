#pragma once
#include <cstdlib>
#include "fundamental.hpp"
#include "fit_count.hpp"
template <typename T>
class block
{
	static inline T* allocate(size_t count)
	{
		if constexpr (fundamental<T>)
			return new T[count];
		else
			return reinterpret_cast<T*>(malloc(count * sizeof(T)));
	}
	static inline void deallocate(T* ptr)
	{
		if constexpr (fundamental<T>)
			delete[] ptr;
		else
			free(ptr);
	}

	T* ptr;
	size_t _count;

public:
	block(size_t count)
		: ptr(allocate(count))
		, _count(count)
	{}
	block(const block&) = delete;
	template <typename U>
	block(block<U>&& other)
		: ptr(reinterpret_cast<T*>(other.ptr))
		, _count(fit_count<sizeof(T), sizeof(U)>(other._count))
	{
		other.ptr = nullptr;
		other._count = 0;
	}
	~block()
	{
		deallocate(ptr);
	}
	void operator=(const block&) = delete;
	template <typename U>
	block& operator=(block<U>&& other)
	{
		swap(ptr, other.ptr);
		swap(_count, other._count);
		return *this;
	}
	operator bool() const
	{
		return ptr;
	}
	size_t count() const
	{
		return _count;
	}
	void release()
	{
		deallocate(ptr);
		ptr = nullptr;
		_count = 0;
	}
	void reset(size_t count)
	{
		deallocate(ptr);
		ptr = allocate(count);
		_count = count;
	}
	T* begin()
	{
		return ptr;
	}
	const T* begin() const
	{
		return ptr;
	}
	T* end()
	{
		return ptr + _count;
	}
	const T* end() const
	{
		return ptr + _count;
	}
	T* operator()(size_t index)
	{
		return ptr + index;
	}
	const T* operator()(size_t index) const
	{
		return ptr + index;
	}
	T& operator[](size_t index)
	{
		return ptr[index];
	}
	const T& operator[](size_t index) const
	{
		return ptr[index];
	}
	bool operator==(const block& other) const
	{
		return ptr == other.ptr;
	}
};