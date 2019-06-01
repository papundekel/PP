#pragma once

template <typename T>
class unique_ptr
{
	T* ptr;
public:
	unique_ptr(T* ptr) : ptr(ptr){}
	unique_ptr(unique_ptr&& move) noexcept : ptr(move.ptr) {move.ptr = nullptr;}
	unique_ptr(const unique_ptr& copy) = delete;
	~unique_ptr()	{delete ptr;}
	T& operator*()	{return *ptr;}
	T* operator->()	{return ptr;}
};