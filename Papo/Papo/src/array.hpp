#pragma once
template <typename T, size_t s>
class array
{
	T* ptr;
public:
	template <size_t size>
	array(const T(&arr)[size])
		: ptr(const_cast<T*>(arr))
	{
		static_assert(size <= s);
	}

	constexpr size_t size()
	{
		return s;
	}
};

template <size_t s, typename T>
array(T(&)[s])->array<T, s>;