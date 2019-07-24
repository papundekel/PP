#pragma once
#include <cstdlib>
#include "mem_cpy.hpp"
#include "fundamental.hpp"
#include "fit_count.hpp"
#include "swap.hpp"
#include "exchange.hpp"
#include "destroy.hpp"

template <typename T>
class block
{
	static inline T* allocate(size_t count)
	{
		return count != 0 ? reinterpret_cast<T*>(malloc(count * sizeof(T))) : nullptr;
	}

	T* ptr;
	size_t cnt;

public:
	block()
		: ptr(nullptr)
		, cnt(0)
	{}
	explicit block(size_t count)
		: ptr(allocate(count))
		, cnt(count)
	{}
	template <typename U>
	block(const block<U>& b, size_t cnt)
		: block(cnt)
	{
		mem_cpy(b.begin(), ptr, fit_count<U, T>(count()));
	}
	block(const block&) = delete;
	template <typename U>
	block(block<U>&& other)
		: ptr(reinterpret_cast<T*>(exchange(other.ptr, nullptr)))
		, cnt(fit_count<T, U>(exchange(other.cnt, 0)))
	{}
	~block()
	{
		free(ptr);
	}
	void operator=(const block&) = delete;
	template <typename U>
	block& operator=(block<U>&& other)
	{
		swap(ptr, other.ptr);
		swap(cnt, other.cnt);
		return *this;
	}
	operator bool() const
	{
		return ptr;
	}
	size_t count() const
	{
		return cnt;
	}
	void release()
	{
		~block();
		new (this) block();
	}
	void reset(size_t count)
	{
		~block();
		new (this) block(count);
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
		return ptr + cnt;
	}
	const T* end() const
	{
		return ptr + cnt;
	}
	T* operator()()
	{
		return ptr;
	}
	T* operator()(size_t index)
	{
		return ptr + index;
	}
	const T* operator()() const
	{
		return ptr;
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