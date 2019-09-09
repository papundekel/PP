#include "list.hpp"
#include <cstring>
#include "sentinel.hpp"
#include "mem_set.hpp"
#include "mem_cpy.hpp"

list<bool>::list()
	: cnt(0)
	, m_block(2)
{}
list<bool>::list(size_t count)
	: cnt(count)
	, m_block(fit_count())
{}
list<bool>::list(size_t count, bool value)
	: cnt(count)
	, m_block(fit_count())
{
	int t;
	value ? t = -1 : t = 0;
	memset(m_block(0), t, m_block.count());
}
list<bool>::list(const list<bool>& other)
	: cnt(other.count())
	, m_block(fit_count())
{
	copy(range(other), range(*this));
}
list<bool>::list(list<bool>&& other) noexcept
	: cnt(other.cnt)
	, m_block(move(other.m_block))
{}

bit_ptr list<bool>::bit(size_t index) const
{
	return { m_block(0), index };
}
list<bool>::iterator list<bool>::begin()
{
	return bit(0);
}
list<bool>::const_iterator list<bool>::begin() const
{
	return bit(0);
}
list<bool>::iterator list<bool>::end()
{
	return bit(cnt);
}
list<bool>::const_iterator list<bool>::end() const
{
	return bit(cnt);
}
bit_ref list<bool>::first()
{
	return bit(0);
}
const bit_ref list<bool>::first() const
{
	return bit(0);
}
bit_ref list<bool>::last()
{
	return bit(cnt - 1);
}
const bit_ref list<bool>::last() const
{
	return bit(cnt - 1);
}
bit_ref list<bool>::operator[](size_t offset)
{
	return bit(offset);
}
const bit_ref list<bool>::operator[](size_t offset) const
{
	return bit(offset);
}

void list<bool>::push_back(bool value)
{
	if (8 * cnt == m_block.count())
	{
		block<unsigned char> new_block(2 * m_block.count());
		copy(range(*this), range(bit_it({ new_block(0), 0 }), infinity()));
		m_block = move(new_block);
	}
	++cnt;
	last() = value;
}
void list<bool>::pop_back()
{
	--cnt;
}

const unsigned char* list<bool>::data() const
{
	return m_block(0);
}
size_t list<bool>::count() const
{
	return cnt;
}
size_t list<bool>::size() const
{
	return m_block.count();
}
size_t list<bool>::capacity() const
{
	return size() * byte_size;
}

size_t list<char>::length(const char* cstring)
{
	size_t length = 0;
	for (const char* temp = cstring;
		*temp != '\0';
		++temp, ++length);
	return length;
}

list<char>& list<char>::_append(const char* cstring, size_t slength)
{
	if (length() + slength > capacity())
	{
		block<char> new_buffer(2 * capacity());
		mem_cpy(buffer.begin(), new_buffer.begin(), length());
		buffer = move(new_buffer);
	}
	mem_cpy(cstring, buffer.begin() + length(), slength);
	m_length += slength;

	return *this;
}
/*list<char> list<char>::_plus(const char* buffer, size_t length) const
{
	list<char> temp(m_length + length);

	memcpy(temp.m_buffer, m_buffer, m_length);
	memcpy(temp.m_buffer + m_length, buffer, length + 1);

	return temp;
}*/

list<char>::list()
	: m_length(0)
	, buffer(16)
{}
list<char>::list(size_t length)
	: m_length(length)
	, buffer(m_length)
{}
list<char>::list(size_t length, char c)
	: m_length(length)
	, buffer(m_length)
{
	mem_set(buffer.begin(), m_length, c);
}
list<char>::list(const char* ptr, size_t length)
	: m_length(length)
	, buffer(m_length)
{
	mem_cpy(ptr, buffer.begin(), m_length);
}
list<char>::list(const char* ptr)
	: list<char>(ptr, length(ptr))
{}
list<char>::list(const list<char>& copy)
	: list<char>(copy.buffer.begin(), copy.length())
{}
list<char>::list(list<char>&& other) noexcept
	: m_length(other.m_length)
	, buffer(move(other.buffer))
{}

list<char>& list<char>::operator=(const list<char>& other)
{
	m_length = other.length();
	buffer.reset(m_length);
	mem_cpy(other.buffer(), buffer(), m_length);
	return *this;
}
list<char>& list<char>::operator=(list<char>&& other) noexcept
{
	swap(m_length, other.m_length);
	swap(buffer, other.buffer);
	return *this;
}
list<char>::iterator list<char>::begin()
{
	return buffer.begin();
}
list<char>::const_iterator list<char>::begin() const
{
	return buffer.begin();
}
list<char>::iterator list<char>::end()
{
	return buffer(length());
}
list<char>::const_iterator list<char>::end() const
{
	return buffer(length());
}
char& list<char>::operator[](size_t index)
{
	return buffer[index];
}
const char& list<char>::operator[](size_t index) const
{
	return buffer[index];
}
char& list<char>::front()
{
	return buffer[0];
}
const char& list<char>::front() const
{
	return buffer[0];
}
char& list<char>::back()
{
	return buffer[length() - 1];
}
const char& list<char>::back() const
{
	return buffer[length() - 1];
}
const char* list<char>::c_str() const
{
	return buffer.begin();
}
size_t list<char>::length() const
{
	return m_length;
}
size_t list<char>::capacity() const
{
	return buffer.count();
}
bool list<char>::empty() const
{
	return m_length == 0;
}
void list<char>::clear()
{
	m_length = 0;
	buffer = block<char>(16);
}
/*
list<char>::iterator list<char>::erase(iterator where)
{
	if (where != end())
	{
		memmove(&*where, &*where + 1, end() - where);
		--m_length;
		return where + 1;
	}
	else
		return where;
}
list<char>::iterator list<char>::erase(iterator begin, iterator end)
{
	if (begin != end)
	{
		size_t count = end - begin;
		memmove(&*begin, &*end, count);
		m_length -= count;
		return begin + 1;
	}
	else
		return begin;
}

void list<char>::shrink_to_fit()
{
	m_capacity = m_length + 1;
	reallocate(m_buffer, m_capacity);
}

bool list<char>::operator==(const char* other) const
{
	return strcmp(m_buffer, other) == 0;
}
bool list<char>::operator==(const list<char>& other) const
{
	return m_length == other.m_length && memcmp(m_buffer, other.m_buffer, m_length) == 0;
}
bool list<char>::operator!=(const char* other) const
{
	return strcmp(m_buffer, other) != 0;
}
bool list<char>::operator!=(const list<char>& other) const
{
	return m_length != other.m_length || memcmp(m_buffer, other.m_buffer, m_length) != 0;
}*/
void list<char>::push_back(char c)
{
	append(c);
}
list<char>& list<char>::append(char c)
{
	if (length() == capacity())
	{
		block<char> new_buffer(2 * capacity());
		mem_cpy(buffer(), new_buffer(), length());
	}

	buffer[m_length] = c;
	return *this;
}
/*list<char>& list<char>::append(const char* other)
{
	_append(other, length(other));
	return *this;
}
list<char>& list<char>::append(const list<char>& other)
{
	_append(other.m_buffer, other.m_length);
	return *this;
}
list<char>& list<char>::operator+=(char c)
{
	return append(c);
}
list<char>& list<char>::operator+=(const char* other)
{
	return _append(other, length(other));
}
list<char>& list<char>::operator+=(const list<char>& other)
{
	return _append(other.m_buffer, other.m_length);
}

list<char> list<char>::operator+(const char* right) const
{
	return _plus(right, length(right));
}
list<char> list<char>::operator+(const list<char>& right) const
{
	return _plus(right.m_buffer, right.m_length);
}

list<char> operator+(const char* left, const list<char>& right)
{
	size_t leftLength = list<char>::length(left);

	list<char> temp(leftLength + right.m_length);

	memcpy(temp.m_buffer, left, leftLength);
	memcpy(temp.m_buffer + leftLength, right.m_buffer, right.m_length + 1);

	return temp;
}*/