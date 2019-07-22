#pragma once
#include "destroy.hpp"
#include <corecrt_malloc.h>
#include <initializer_list>
#include <vcruntime_string.h>
#include "conditional.hpp"
#include "int.hpp"

template<typename T>
class circular_list
{
	size_t _count;
	size_t _capacity;
	T* buffer;
	iterator<T> _begin;

	void tidy()
	{
		if (buffer)
		{
			destroy(begin(), end());
			free(buffer);
		}
	}

	class index_out_of_range {};

public:
	explicit circular_list(size_t capacity)
		: _count(0)
		, _capacity(capacity)
		, buffer(allocate<T>(_capacity))
		, _begin({ buffer, _capacity, buffer, false })
	{}
	circular_list()
		: circular_list(16)
	{}
	/*explicit circular_list(const char* filename)
	{
		std::ifstream file(filename);

		file.read(reinterpret_cast<char*>(&_count), sizeof(size_t));
		_capacity = _count;
		buffer = allocate<T>(_capacity);

		file.read(reinterpret_cast<char*>(buffer), _count * sizeof(T));
		file.close();
	}*/
	circular_list(size_t count, size_t capacity)
		: _count(min(count, capacity))
		, _capacity(capacity)
		, buffer(allocate<T>(_capacity))
		, _begin({ buffer, _capacity, buffer, false })
	{
		default_construct<T>(begin(), end());
	}
	circular_list(size_t count, size_t capacity, const T& value)
		: _count(min(count, capacity))
		, _capacity(capacity)
		, buffer(allocate<T>(_capacity))
		, _begin({ buffer, _capacity, buffer, false })
	{
		u_fill(begin(), end(), value);
	}
	circular_list(size_t count, T(&g)())
		: _count(count)
		, _capacity(count)
		, buffer(allocate<T>(_capacity))
		, _begin({ buffer, _capacity, buffer, false })
	{
		u_generate(begin(), end(), g);
	}
	template <typename it, typename =
	enable_if<is_iterator<it>>>
	circular_list(it first, it last)
		: _count(distance(first, last))
		, _capacity(count)
		, buffer(allocate<T>(_capacity))
		, _begin({ buffer, _capacity, buffer, false })
	{
		u_copy(first, last, begin());
	}
	circular_list(const std::initializer_list<T>& list)
		: _count(list.size())
		, _capacity(_count)
		, buffer(allocate<T>(_capacity))
		, _begin({ buffer, _capacity, buffer, false })
	{
		u_copy(list.begin(), list.end(), begin());
	}
	circular_list(const list<T>& copy)
		: _count(copy._count)
		, _capacity(copy._capacity)
		, buffer(allocate<T>(_capacity))
		, _begin({ buffer, _capacity, buffer, false })
	{
		u_copy(copy.begin(), copy.end(), begin());
	}
	circular_list(list<T>&& move) noexcept
		: _count(move._count)
		, _capacity(move._capacity)
		, buffer(move.buffer)
		, _begin(move._begin)
	{
		move.buffer = nullptr;
	}
	~circular_list()
	{
		tidy();
	}

	template <typename U>
	class iterator
	{
		U* buffer;
		size_t capacity;
		U* ptr;
		bool reverse_order;

	public:
		iterator(U* buffer, size_t capacity, U* ptr, bool reverse_order)
			: buffer(buffer)
			, capacity(capacity)
			, ptr(ptr)
			, reverse_order(reverse_order)
		{}
		U* operator->() const
		{
			return ptr;
		}
		U& operator*() const
		{
			return *ptr;
		}
		U& operator[](diff offset) const
		{
			return *(*this + offset);
		}
		iterator& operator++()
		{
			++ptr;
			if (!reverse_order && ptr == buffer + capacity)
			{
				ptr = buffer;
				reverse_order = true;
			}
			return *this;
		}
		iterator operator++(int)
		{
			auto temp = *this;
			++*this;
			return temp;
		}
		iterator& operator--()
		{
			if (reverse_order && ptr == buffer)
			{
				ptr = buffer + capacity - 1;
				reverse_order = false;
			}
			else
				--ptr;
			return *this;
		}
		iterator operator--(int)
		{
			auto temp = *this;
			--*this;
			return temp;
		}
		iterator operator+(diff other) const
		{
			if (!reverse_order && ptr + other >= buffer + capacity)
				return { buffer, capacity, ptr + other - capacity, true };
			else
				return { buffer, capacity, ptr + other, reverse_order };
		}
		iterator operator-(diff other) const
		{
			if (reverse_order && ptr - other < buffer)
				return { buffer, capacity, ptr - other + capacity , false };
			else
				return { buffer, capacity, ptr - other, reverse_order };
		}
		diff operator-(iterator other) const
		{
			if (reverse_order == other.reverse_order)
				return ptr - other.ptr
			else if (reverse_order)
				return ptr - other.ptr + capacity;
			else
				return ptr - other.ptr - capacity;
		}
		bool operator==(iterator other) const
		{
			return ptr == other.ptr && reverse_order == other.reverse_order;
		}
		bool operator!=(iterator other) const
		{
			return ptr != other.ptr || reverse_order != other.reverse_order;
		}
		bool operator<(iterator other) const
		{
			return *this - other < 0;
		}
	};

	iterator<T> begin()
	{
		return _begin;
	}
	iterator<const T> begin() const
	{
		return _begin;
	}
	iterator<T> end()
	{
		return _begin + _count;
	}
	iterator<const T> end() const
	{
		return _begin + _count;
	}
	T& front()
	{
		return *_begin;
	}
	const T& front() const
	{
		return *_begin;
	}
	T& back()
	{
		return *end();
	}
	const T& back() const
	{
		return *end();
	}
	bool empty() const
	{
		return _count == 0;
	}
	size_t count() const
	{
		return _count;
	}
	size_t size() const
	{
		return _count * sizeof(T) + sizeof(list<T>);
	}
	size_t capacity() const
	{
		return _capacity;
	}
	void clear(size_t capacity = 16)
	{
		tidy();

		_count = 0;
		_capacity = capacity;
		buffer = allocate<T>(_capacity);
		_begin = { buffer, capacity, buffer, reverse_order };
	}
	/*void shrink_to_fit()
	{
		if (_capacity != _count)
		{
			_capacity = _count;
			auto new_buffer = allocate<T>(_capacity);

			u_move(begin(), end(), new_buffer);

			tidy();

			buffer = new_buffer;
		}
	}*/
	circular_list<T>& operator=(const circular_list<T>& right)
	{
		if (right != *this)
		{
			tidy();

			_count = right._count;
			_capacity = right._capacity;
			buffer = allocate<T>(_capacity);
			_begin = { buffer, _capacity, _begin, false };

			u_copy(right.buffer, right.buffer + _count, buffer);
		}

		return *this;
	}
	list<T>& operator=(list<T>&& right) noexcept
	{
		if (m_buffer != right.m_buffer)
			swap(right);
		return *this;
	}

	T& operator[](size_t index)
	{
		return _begin[index];
	}
	const T& operator[](size_t index) const
	{
		return _begin[index];
	}

	/*T& at(size_t index)
	{
		if (index < m_count)
			return m_buffer[index];
		else
			throw index_out_of_range();
	}
	const T& at(size_t index) const
	{
		if (index < m_count)
			return m_buffer[index];
		else
			throw index_out_of_range();
	}
	bool operator==(const circular_list& other) const
	{
		return m_buffer == other.m_buffer || equal(range(*this), other.begin());
	}
	bool operator!=(const circular_list& other) const
	{
		return !(*this == other);
	}*/
	/*template <typename U>
	void insert(iterator where, U&& value)
	{
		if (m_count != m_capacity)
		{
			if (m_count != 0)
			{
				construct(end(), std::move(*(end() - 1)));
				move_backward(where, end() - 1, end());
				*where = std::forward<U>(value);
			}
			else
				construct(m_buffer, std::forward<U>(value));
		}
		else
		{
			m_capacity *= 2;
			auto new_buffer = allocate<T>(m_capacity);
			auto it = new_buffer;

			it = u_move(begin(), where, it);
			construct(it, std::forward<U>(value));
			u_move(where, end(), it + 1);

			tidy();
			m_buffer = new_buffer;
		}
		++m_count;
	}
	void insert(iterator where, const std::initializer_list<T> & init_list)
	{
		if (m_count + init_list.size() <= m_capacity)
		{
			size_t dist = distance(where, end());
			if (init_list.size() <= dist)
			{
				u_move_backward_n(init_list.size(), end(), end() + init_list.size());
				move_backward(where, end() - init_list.size(), end());
				copy(init_list.begin(), init_list.end(), where);
			}
			else
			{
				auto x = u_move_backward_n(dist, end(), end() + init_list.size());
				u_copy_backward_n(init_list.size() - dist, init_list.end(), x);
				copy_n(init_list.begin(), dist, where);
			}
		}
		else
		{
			m_capacity *= 2;
			auto new_buffer = allocate<T>(m_capacity);
			auto it = new_buffer;

			it = u_move(begin(), where, it);
			it = u_copy(init_list.begin(), init_list.end(), it);
			u_move(where, end(), it);

			tidy();
			m_buffer = new_buffer;
		}
		m_count += init_list.size();
	}
	template <typename U>
	void insert(size_t index, U && value)
	{
		insert(m_buffer + index, std::forward(value));
	}
	void insert(size_t index, const std::initializer_list<T> & init_list)
	{
		insert(m_buffer + index, init_list);
	}*/
	template <typename U>
	void push_front(U&& value)
	{
		if (_count != _capacity)
		{
			--_begin
			construct(begin(), std::forward<U>(value));
		}
		else
		{
			_capacity *= 2;
			auto new_buffer = allocate<T>(_capacity);

			u_move(begin(), end(), new_buffer + 1);
			construct(new_buffer, std::forward<U>(value));

			tidy();

			_buffer = new_buffer;
			_begin = buffer;
		}
		++_count;
	}
	template <typename U>
	void push_back(U&& value)
	{
		if (_count != _capacity)
			construct(end(), std::forward<U>(value));
		else
		{
			_capacity *= 2;
			auto new_buffer = allocate<T>(_capacity);

			u_move(begin(), end(), new_buffer);
			construct(new_buffer + _count, std::forward<U>(value));

			tidy();

			_buffer = new_buffer;
			_begin = _buffer;
		}
		++_count;
	}
	/*void pop_back()
	{
		destroy_at(end());
		--m_count;
	}

	iterator erase(iterator where)
	{
		destroy_at(where);
		move(where + 1, end(), where);
		--m_count;
		return where + 1;
	}
	iterator erase(iterator begin, iterator end)
	{
		for (; begin != end; ++begin)
			destroy_at(begin);
		m_count -= distance(begin, end);
		return begin;
	}*/

	template <typename T>
	friend void swap(circular_list<T>& left, circular_list<T>& right);
};

template <typename T>
void swap(circular_list<T>& left, circular_list<T>& right)
{
	constexpr size_t s = sizeof(circular_list<T>);
	char buffer[s];
	memcpy(buffer, &left, s);
	memcpy(&left, &right, s);
	memcpy(&right, buffer, s);
}