#pragma once
#include <cstdlib>
#include "ref.hpp"
#include "type.hpp"
#include "equal.hpp"
#include "swap.hpp"

namespace dblock
{
	template <typename T>
	class block
	{
		size_t cnt;
		T* data;
	public:
		block()
			: cnt(0)
			, data(nullptr)
		{}
		explicit block(size_t count)
			: cnt(count)
    		, data(reinterpret_cast<T*>(malloc(count * sizeof(T))))
		{}
		block(const block&) = delete;
		block(block&& other)
			: cnt(other.cnt)
			, data(other.data)
		{
			other.data = nullptr;
		}
		~block()
		{
			free(data);
		}
		block& operator=(const block&) = delete;
		block& operator=(block&& other)
		{
			if (this != &other)
			{
				swap(cnt, other.cnt);
				swap(data, other.data);
			}
			return *this;
		}
		block& reset(size_t count = 0)
		{
			this->~block();
			new (this) block(count);
			return *this;
		}
		T* begin()
		{
			return data;
		}
		const T* begin() const
		{
			return data;
		}
		size_t count() const
		{
			return cnt;
		}
		T* end()
		{
			return begin() + count();
		}
		const T* end() const
		{
			return begin() + count();
		}
		operator bool() const
		{
			return begin();
		}
		bool operator==(const block& other) const
		{
			return this == &other || equal(range(*this), range(other));
		}
		T* operator()(size_t index = 0)
		{
			return begin() + index;
		}
		const T* operator()(size_t index = 0) const
		{
			return begin() + index;
		}
		T& operator[](size_t index)
		{
			return begin()[index];
		}
		const T& operator[](size_t index) const
		{
			return begin()[index];
		}
	};

	template <typename T>
	struct x : type<block<T>> {};
	template <typename T>
	struct x<T&> : type<block<ref<T>>> {};
}

template <typename T>
using block = dblock::x<T>::t;