#pragma once
#include <cstdlib>
#include "mem_cpy.hpp"
#include "fit_count.hpp"
#include "swap.hpp"
#include "exchange.hpp"
#include "remove_const.hpp"
#include "ref.hpp"
#include "type_t.hpp"

namespace detail
{
	template <typename T>
	class block_impl
	{
		T* ptr;
		size_t cnt;

	public:
		explicit block_impl(size_t count = 0)
			: ptr(count != 0 ? reinterpret_cast<T*>(malloc(count * sizeof(T))) : nullptr)
			, cnt(count)
		{}
		block_impl(const block_impl&) = delete;
		block_impl(block_impl&& other)
			: ptr(exchange(other.ptr, nullptr))
			, cnt(exchange(other.cnt, 0))
		{}
		~block_impl()
		{
			free(ptr);
		}
		block_impl& operator=(const block_impl& other) = delete;
		block_impl& operator=(block_impl&& other)
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
		block_impl& reset(size_t count = 0)
		{
			this->~block_impl();
			new (this) block_impl(count);
			return *this;
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
		T* operator()(size_t index = 0)
		{
			return ptr + index;
		}
		const T* operator()(size_t index = 0) const
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
		bool operator==(const block_impl& other) const
		{
			return ptr == other.ptr;
		}
	};

	template <typename T>
	struct block : type_t<block_impl<T>> {};
	template <typename T>
	struct block<T&> : type_t<block_impl<ref<T>>> {};
}

template <typename T>
using block = detail::block<T>::t;