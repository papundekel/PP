#pragma once
#include "int.hpp"
#include <initializer_list>
#include "destroy.hpp"
#include "copy.hpp"
#include "fill.hpp"
#include "u_copy.hpp"
#include "u_move.hpp"
#include "u_fill.hpp"
#include "u_generate.hpp"
#include "range.hpp"
#include "bit.hpp"
#include "swap.hpp"
#include "block.hpp"
#include "move_backward.hpp"
#include "forward.hpp"
#include "next.hpp"
#include "equal.hpp"

template<typename T, size_t cnt = 0> class list
{
public:
	T buffer[cnt];

	T* begin()
	{
		return buffer;
	}
	const T* begin() const
	{
		return buffer;
	}
	T* end()
	{
		return buffer + cnt;
	}
	const T* end() const
	{
		return buffer + cnt;
	}
	operator T*()
	{
		return buffer;
	}
	operator const T*() const
	{
		return buffer;
	}
	T& operator[](size_t offset)
	{
		return buffer[offset];
	}
	const T& operator[](size_t offset) const
	{
		return buffer[offset];
	}
	constexpr auto count() const
	{
		return cnt;
	}
};

template<typename T> class list<T>
{
	size_t cnt;
	block<T> buffer;

public:
	list()
		: cnt(0)
		, buffer(16)
	{}
	explicit list(size_t cap)
		: cnt(0)
		, buffer(cap)
	{}
	template <typename ...Args>
	list(size_t cnt, size_t cap, Args&&... args)
		: cnt(cnt)
		, buffer(cap)
	{
		u_fill(range(*this), forward<Args>(args)...);
	}
	template <typename G>
	list(size_t cnt, size_t cap, G g)
		: cnt(cnt)
		, buffer(cap)
	{
		u_generate(range(*this), g);
	}
	template <typename R>
	requires range_type<R>::v
	list(R r)
		: cnt(r.count())
		, buffer(cnt)
	{
		u_copy(r, range(*this));
	}
	list(const list<T>& copy)
		: list(range(copy))
	{}
	list(list<T>&& other) noexcept
		: cnt(exchange(other.cnt, 0))
		, buffer(move(other.buffer))
	{}
	~list()
	{
		destroy(range(*this));
	}

	T* begin()
	{
		return buffer(0);
	}
	const T* begin() const
	{
		return buffer(0);
	}
	T* end()
	{
		return buffer(cnt);
	}
	const T* end() const
	{
		return buffer(cnt);
	}
	T* operator()(size_t index)
	{
		return buffer(index);
	}
	const T* operator()(size_t index) const
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
		return buffer[cnt - 1];
	}
	const T& back() const
	{
		return buffer[cnt - 1];
	}
	bool empty() const
	{
		return cnt == 0;
	}
	size_t count() const
	{
		return cnt;
	}
	size_t size() const
	{
		return cnt * sizeof(T) + sizeof(list<T>);
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
		cnt = 0;
		buffer.reset(capacity);
	}
	void shrink_to_fit()
	{
		if (buffer.count() != cnt)
		{
			block<T> new_buffer(cnt);
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

			cnt = right.count();
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

	bool operator==(const list& other) const
	{
		return buffer == other.buffer || equal(range(*this), range(other));
	}

	template <typename U>
	void insert(T* where, U&& value)
	{
		if (cnt != buffer.count())
		{			
			if (cnt != 0)
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
		++cnt;
	}
	template <typename R>
	requires range_type<R>::v
	void insert(T* where, R what)
	{
		auto size = distance(what);

		if (cnt + size <= buffer.count())
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
		cnt += size;
	}
	template <typename U>
	void insert(size_t index, U&& value)
	{
		insert(buffer(index), forward<U>(value));
	}
	template <typename R>
	requires range_type<R>::v
	void insert(size_t index, R what)
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
		++cnt;
	}
	void pop_back()
	{
		destroy_at(end());
		--cnt;
	}

	T* erase(T* where)
	{
		destroy_at(where);
		range r(where, end());
		move(r + 1, r);
		--cnt;
		return next(where);
	}
	T* erase(range<T*> r)
	{
		destroy(r);
		cnt -= distance(r);
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
	{}
	list(bool value)
	{
		int t = value ? 1 : 0;
		memset(buffer, t, byte_count);
	}
	list(const list& other)
	{
		copy(range(other), range(*this));
	}
	template <typename R>
	requires range_type<R>::v
	list(R r)
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
	size_t cnt;
	block<unsigned char> m_block;

	constexpr size_t fit_count()
	{
		return ::fit_count<byte_size, sizeof(unsigned char)>(cnt);
	}

	bit_ptr bit(size_t index) const;
public:
	list();
	list(size_t count);
	list(size_t count, bool value);
	template <typename it, typename it_end>
	list(range<it, it_end> r)
		: cnt(distance(r))
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
	list(const list& copy);
	list(list&& move) noexcept;

	list& operator=(const list& other);
	list& operator=(list&& other) noexcept;

	using		iterator = char*;
	using const_iterator = const char*;

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

template <typename R>
requires range_type<R>::v
list(R) -> list<remove_cv<range_base<R>>>;

template <typename T>
void swap(list<T>& left, list<T>& right)
{
	swap(left.cnt, right.cnt);
	swap(left.buffer, right.buffer);
}