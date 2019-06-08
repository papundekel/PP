#pragma once
#include <initializer_list>
#include <functional>
#include <fstream>
#include "destroy.hpp"
#include "iterator_random_access.hpp"
#include "copy.hpp"
#include "fill.hpp"
#include "u_copy.hpp"
#include "u_move.hpp"
#include "u_fill.hpp"
#include "u_generate.hpp"
#include "distance.hpp"
#include "range.hpp"
#include "bit.hpp"
#include "swap.hpp"
#include "block.hpp"
#include "move_backward.hpp"
#include "u_move_backward_n.hpp"
#include "forward.hpp"
#include "next.hpp"
#include "equal.hpp"

template<typename T, size_t count = 0> class list
{
	T m_buffer[count];

public:
	list() = default;
	template <typename it, typename it_end>
	list(range<it, it_end> r)
	{
		copy(r, range(*this));
	}
	list(const std::initializer_list<T>& list)
	{
		auto i = copy(range(list), range(*this));
		fill(range(i, end()));
	}
	~list() = default;

	using		iterator = iterator_random_access<T>;
	using const_iterator = iterator_random_access<const T>;

	iterator begin()
	{
		return m_buffer;
	}
	const_iterator begin() const
	{
		return m_buffer;
	}
	iterator end()
	{
		return m_buffer + count;
	}
	const_iterator end() const
	{
		return m_buffer + count;
	}
	operator T*()
	{
		return m_buffer;
	}
	operator const T*() const
	{
		return m_buffer;
	}
	T& operator[](size_t offset)
	{
		return m_buffer[offset];
	}
	const T& operator[](size_t offset) const
	{
		return m_buffer[offset];
	}
	constexpr size_t size() const
	{
		return count;
	}
};
template<typename T> class list<T>
{
	size_t m_count;
	block<T> buffer;

	class index_out_of_range{};

	static size_t file_count(const char* filename)
	{
		size_t result;
		std::ifstream file(filename);
		file.read(reinterpret_cast<char*>(&result), sizeof(size_t));
		file.close();
		return result;
	}

public:
	list()
		: m_count(0)
		, buffer(16)
	{}
	explicit list(const char* filename)
		: m_count(file_count(filename))
		, buffer(m_count)
	{
		std::ifstream file(filename);

		file.read(reinterpret_cast<char*>(buffer(0)), m_count * sizeof(T));
		file.close();
	}
	explicit list(size_t capacity)
		: m_count(0)
		, buffer(capacity)
	{}
	list(size_t count, size_t capacity)
		: m_count(count)
		, buffer(capacity)
	{
		if (count > capacity)
			m_count = capacity;
		construct<T>(range(*this));
	}
	list(size_t count, size_t capacity, const T& value)
		: m_count(count)
		, buffer(capacity)
	{
		u_fill(range(*this), value);
	}
	list(size_t count, T(&g)())
		: m_count(count)
		, buffer(m_count)
	{
		u_generate(range(*this), g);
	}
	template <typename it, typename it_end>
	list(range<it, it_end> r)
		: m_count(distance(r))
		, buffer(m_count)
	{
		u_copy(r, range(*this));
	}
	list(const list<T>& copy)
		: m_count(copy.count())
		, buffer(m_count)
	{
		u_copy(range(copy), range(*this));
	}
	list(list<T>&& other) noexcept
		: m_count(other.count())
		, buffer(move(other.buffer))
	{}
	~list()
	{
		if (buffer)
			destroy(range(*this));
	}

    using		iterator = iterator_random_access<		T>;
    using const_iterator = iterator_random_access<const T>;

	iterator begin()
	{
		return buffer(0);
	}
	const_iterator begin() const
	{
		return buffer(0);
	}
	iterator end()
	{
		return buffer(m_count);
	}
	const_iterator end() const
	{
		return buffer(m_count);
	}
	iterator operator()(size_t index)
	{
		return buffer(index);
	}
	const_iterator operator()(size_t index) const
	{
		return buffer(index);
	}
	T& front()
	{
		return buffer[0];
	}
	const T& front() const
	{
		return buffer[0];
	}
	T& back()
	{
		return buffer[m_count - 1];
	}
	const T& back() const
	{
		return buffer[m_count - 1];
	}
	bool empty() const
	{
		return m_count == 0;
	}
	size_t count() const
	{
		return m_count;
	}
	size_t size() const
	{
		return m_count * sizeof(T) + sizeof(list<T>);
	}
	size_t capacity() const
	{
		return buffer.count();
	}
	T* data()
	{
		return buffer(0);
	}
	const T* data() const
	{
		return buffer(0);
	}
	void clear(size_t capacity = 16)
	{
		destroy(range(*this));
		m_count = 0;
		buffer.reset(capacity);
	}
	void shrink_to_fit()
	{
		if (buffer.count() != m_count)
		{
			block<T> new_buffer(m_count);
			u_move(range(*this), range(new_buffer));
			destroy(range(*this));
			buffer = move(new_buffer);
		}
	}
	list<T>& operator=(const list<T>& right)
	{
		if (right != *this)
		{
			destroy(range(*this));

			m_count = right.count();
			buffer = move(right.buffer);

			u_copy(range(right), range(*this));
		}

		return *this;
	}
	list<T>& operator=(list<T>&& right) noexcept
	{
		if (buffer != right.buffer)
			swap(*this, right);
		return *this;
	}

	T& operator[](size_t index)
	{
		return buffer[index];
	}
	const T& operator[](size_t index) const
	{
		return buffer[index];
	}

	T& at(size_t index)
	{
		if (index < m_count)
			return buffer[index];
		else
			throw index_out_of_range();
	}
	const T& at(size_t index) const
	{
		if (index < m_count)
			return buffer[index];
		else
			throw index_out_of_range();
	}
	bool operator==(const list& other) const
	{
		return buffer == other.buffer || equal(range(*this), range(other));
	}
	bool operator!=(const list& other) const
	{
		return !(*this == other);
	}
	template <typename U>
	void insert(iterator where, U&& value)
	{
		if (m_count != buffer.count())
		{			
			if (m_count != 0)
			{
				construct(end(), move(back()));
				move_backward(range(where, end() - 1), range(*this));
				*where = forward<U>(value);
			}
			else
				construct(buffer.begin(), forward<U>(value));
		}
		else
		{
			block<T> new_buffer(2 * capacity());
			range r(new_buffer);

			construct(u_move(range(begin(), where), r), forward<U>(value));
			u_move(range(where, end()), r + 1);

			destroy(range(*this));
			buffer = move(new_buffer);
		}
		++m_count;
	}
	template <typename it, typename it_end>
	void insert(iterator where, range<it, it_end> what)
	{
		auto size = distance(what);

		if (m_count + size <= buffer.count())
		{
			size_t dist = distance({ where, end() });
			if (size <= dist)
			{
				u_move_backward_n(size, end(), end() + size);
				move_backward(where, end() - size, end());
				copy(what, where);
			}
			else
			{
				auto x = u_move_backward_n(dist, end(), end() + size);
				u_copy_backward_n(size - dist, what.end, x);
				copy_n(what.begin, dist, where);
			}
		}
		else
		{
			block<T> new_buffer(2 * capacity());
			range r(new_buffer);

			r.begin = u_move({ begin(), where }, r);
			r.begin = u_copy(what, r);
			u_move({ where, end() }, r);

			destroy(range(*this));
			buffer = move(new_buffer);
		}
		m_count += size;
	}
	template <typename U>
	void insert(size_t index, U&& value)
	{
		insert(buffer(index), forward<U>(value));
	}
	template <typename it, typename it_end>
	void insert(size_t index, range<it, it_end> what)
	{
		insert(buffer(index), what);
	}
	template <typename U>
	void push_back(U&& value)
	{
		if (count() != capacity())
			construct(end(), forward<U>(value));
		else
		{
			block<T> new_buffer(2 * capacity());
			u_move(range(*this), range(new_buffer));
			construct(new_buffer(count()), forward<U>(value));

			destroy(range(*this));

			buffer = move(new_buffer);
		}
		++m_count;
	}
	void pop_back()
	{
		destroy_at(end());
		--m_count;
	}

	iterator erase(iterator where)
	{
		destroy_at(where);
		range r(where, end());
		move(r + 1, r);
		--m_count;
		return next(where);
	}
	template <typename it, typename it_end>
	iterator erase(range<it, it_end> r)
	{
		for (; r.begin != r.end; ++r.begin)
			destroy_at(r.begin);
		m_count -= distance(r);
		return r.begin;
	}

	template <typename U>
	friend void swap(list<U>& left, list<U>& right);
};
template<size_t count> class list<bool, count>
{
	static constexpr size_t byte_count = ::fit_count<byte_size, 1>(count);
	unsigned char buffer[byte_count];

	bit_ptr bit(size_t index) const
	{
		return bit_ptr(buffer, index);
	}
public:

	list()
		: buffer()
	{}
	list(bool value)
		: buffer()
	{
		int t = value ? 1 : 0;
		memset(buffer, t, byte_count);
	}
	list(const list& other)
		: buffer()
	{
		copy(range(other), range(*this));
	}
	template <typename it, typename it_end>
	list(range<it, it_end> r)
		: buffer()
	{
		copy(r, range(*this));
	}

	using iterator = bit_it;
	using const_iterator = const_bit_it;
	iterator begin()
	{
		return bit(0);
	}
	const_iterator begin() const
	{
		return bit(0);
	}
	iterator end()
	{
		return bit(count);
	}
	const_iterator end() const
	{
		return bit(count);
	}
	bit_ref operator[](size_t offset)
	{
		return bit(offset);
	}
	const bit_ref operator[](size_t offset) const
	{
		return bit(offset);
	}

	constexpr size_t size() const
	{
		return byte_count;
	}
};
template<> class list<bool>
{
	size_t m_count;
	block<unsigned char> m_block;

	constexpr size_t fit_count()
	{
		return ::fit_count<byte_size, sizeof(unsigned char)>(m_count);
	}

	bit_ptr bit(size_t index) const;
public:
	list();
	list(size_t count);
	list(size_t count, bool value);
	template <typename it, typename it_end>
	list(range<it, it_end> r)
		: m_count(distance(r))
		, m_block(fit_count())
	{
		copy(r, range(*this));
	}
	list(const list& copy);
	list(list&& move) noexcept;

	using iterator = bit_it;
	using const_iterator = const_bit_it;
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	bit_ref first();
	const bit_ref first() const;
	bit_ref last();
	const bit_ref last() const;
	bit_ref operator[](size_t offset);
	const bit_ref operator[](size_t offset) const;

	void push_back(bool value);
	void pop_back();

	const unsigned char* data() const;
	size_t count() const;
	size_t size() const;
	size_t capacity() const;
};
template<> class list<char>
{
	size_t m_length;
	block<char> buffer;

	list& _append(const char* buffer, size_t length);
	list _plus(const char* buffer, size_t length) const;
public:
	list();
	explicit list(size_t length);
	list(size_t count, char c);
	list(const char* ptr);
	list(const char* const ptr, size_t length);
	/*template <typename it>
	list(it begin, it end)
		: m_length(distance(begin, end))
		, m_capacity(m_length + 1)
		, m_buffer(new char[m_capacity])
	{
		copy(begin, end, m_buffer);
	}*/
	list(const list&copy);
	list(list&& move) noexcept;

	list& operator=(const list& other);
	list& operator=(list&& other) noexcept;

	using		iterator = iterator_random_access<char>;
	using const_iterator = iterator_random_access<const char>;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	char& front();
	const char& front() const;
	char& back();
	const char& back() const;

	const char* c_str() const;
	size_t length() const;
	size_t capacity() const;
	bool empty() const;
	void shrink_to_fit();

	void clear();
	iterator erase(iterator where);
	iterator erase(iterator begin, iterator end);

	bool operator==(const char* other) const;
	bool operator==(const list& other) const;
	bool operator!=(const char* other) const;
	bool operator!=(const list& other) const;

	void push_back(char c);

	list& append(char c);
	list& append(const char* const other);
	list& append(const list& other);
	list& operator+=(char c);
	list& operator+=(const char* other);
	list& operator+=(const list& other);

	list operator+(const char* const right) const;
	list operator+(const list& right) const;
	friend list operator+(const char* const left, const list& right);

	static size_t length(const char* cstring);
};

using string = list<char>;

template <typename it, typename it_end> list(range<it, it_end>)->list<base_type<it>>;

template <typename T>
void swap(list<T>& left, list<T>& right)
{
	swap(left.m_count, right.m_count);
	swap(left.buffer, right.buffer);
}