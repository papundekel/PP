#include "string.hpp"
#include "reallocate.hpp"
#include <cstring>
#include "swap.hpp"
#include <iostream>

size_t string::length(const char* cstring)
{
	size_t length = 0;
	for (const char* temp = cstring;
		*temp != '\0';
		++temp, ++length);
	return length;
}

string& string::_append(const char* buffer, size_t length)
{
	if (m_length + length + 1 > m_capacity)
	{
		m_capacity *= 2;
		reallocate(m_buffer, m_capacity);
	}
	memcpy(m_buffer + m_length, buffer, length + 1);
	m_length += length;

	return *this;
}
string string::_plus(const char* buffer, size_t length) const
{
	string temp(m_length + length);

	memcpy(temp.m_buffer, m_buffer, m_length);
	memcpy(temp.m_buffer + m_length, buffer, length + 1);

	return temp;
}

string::string()
	: m_length(0)
	, m_capacity(16)
	, m_buffer(new char[m_capacity])
{
	m_buffer[0] = '\0';
}
string::string(size_t length)
	: m_length(length)
	, m_capacity(m_length + 1)
	, m_buffer(new char[m_capacity])
{}
string::string(size_t count, char c)
	: m_length(count)
	, m_capacity(m_length + 1)
	, m_buffer(new char[m_capacity])
{
	memset(m_buffer, c, count);
	m_buffer[m_length] = '\0';
}
string::string(const char* ptr)
	: m_length(length(ptr))
	, m_capacity(m_length + 1)
	, m_buffer(new char[m_capacity])
{
	memcpy(m_buffer, ptr, m_capacity);
}
string::string(const char* ptr, size_t length)
	: m_length(length)
	, m_capacity(m_length + 1)
	, m_buffer(new char[m_capacity])
{
	memcpy(m_buffer, ptr, length);
	m_buffer[length] = '\0';
}
string::string(const string& copy)
	: m_length(copy.m_length)
	, m_capacity(copy.m_capacity)
	, m_buffer(new char[m_capacity])
{
	memcpy(m_buffer, copy.m_buffer, m_length + 1);
}
string::string(string&& move) noexcept
	: m_length(move.m_length)
	, m_capacity(move.m_capacity)
	, m_buffer(move.m_buffer)
{
	move.m_buffer = nullptr;
}
string::~string()
{
	delete[] m_buffer;
}

string& string::operator=(const string& other)
{
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	reallocate(m_buffer, m_capacity);
	memcpy(m_buffer, other.m_buffer, other.m_length + 1);
	return *this;
}
string& string::operator=(string&& other) noexcept
{
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	swap(m_buffer, other.m_buffer);
	return *this;
}

string::iterator string::begin()
{
	return m_buffer;
}
string::const_iterator string::begin() const
{
	return m_buffer;
}
string::iterator string::end()
{
	return m_buffer + m_length;
}
string::const_iterator string::end() const
{
	return m_buffer + m_length;
}
char& string::operator[](size_t index)
{
	return m_buffer[index];
}
const char& string::operator[](size_t index) const
{
	return m_buffer[index];
}
char& string::front()
{
	return m_buffer[0];
}
const char& string::front() const
{
	return m_buffer[0];
}
char& string::back()
{
	return m_buffer[m_length - 1];
}
const char& string::back() const
{
	return m_buffer[m_length - 1];
}
const char* string::c_str() const
{
	return m_buffer;
}
size_t string::length() const
{
	return m_length;
}
size_t string::capacity() const
{
	return m_capacity;
}
bool string::empty() const
{
	return m_length == 0;
}
void string::clear()
{
	m_length = 0;
	m_capacity = 16;
	reallocate(m_buffer, m_capacity);
	m_buffer[0] = '\0';
}

string::iterator string::erase(iterator where)
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
string::iterator string::erase(iterator begin, iterator end)
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

void string::shrink_to_fit()
{
	m_capacity = m_length + 1;
	reallocate(m_buffer, m_capacity);
}

bool string::operator==(const char* other) const
{
	return strcmp(m_buffer, other) == 0;
}
bool string::operator==(const string& other) const
{
	return m_length == other.m_length && memcmp(m_buffer, other.m_buffer, m_length) == 0;
}
bool string::operator!=(const char* other) const
{
	return strcmp(m_buffer, other) != 0;
}
bool string::operator!=(const string& other) const
{
	return m_length != other.m_length || memcmp(m_buffer, other.m_buffer, m_length) != 0;
}
string& string::append(char c)
{
	if ((m_length + 1) + 1 > m_capacity)
	{
		m_capacity *= 2;
		reallocate(m_buffer, m_capacity);
	}
	m_buffer[m_length] = c;
	++m_length;
	m_buffer[m_length] = '\0';
	return *this;
}
string& string::append(const char* other)
{
	_append(other, length(other));
	return *this;
}
string& string::append(const string& other)
{
	_append(other.m_buffer, other.m_length);
	return *this;
}
string& string::operator+=(char c)
{
	return append(c);
}
string& string::operator+=(const char* other)
{
	return _append(other, length(other));
}
string& string::operator+=(const string& other)
{
	return _append(other.m_buffer, other.m_length);
}

string string::operator+(const char* right) const
{
	return _plus(right, length(right));
}
string string::operator+(const string& right) const
{
	return _plus(right.m_buffer, right.m_length);
}

std::ostream& operator<<(std::ostream& cout, const string& str)
{
	cout << str.m_buffer;
	return cout;
}

string operator+(const char* left, const string& right)
{
	size_t leftLength = string::length(left);

	string temp(leftLength + right.m_length);

	memcpy(temp.m_buffer, left, leftLength);
	memcpy(temp.m_buffer + leftLength, right.m_buffer, right.m_length + 1);

	return temp;
}

string to_string(int x)
{
	int count = 0;
	int divisor = 1;
	for (int i = x; i != 0; i /= 10, divisor *= 10)
		++count;

	string s(count);

	if (x < 0)
	{
		x = -x;
		s.append('-');
	}

	while (x != 0)
	{
		s.append('0' + x / divisor);
		x %= divisor;
		divisor /= 10;
	}

	return s;
}

void getline(std::istream& cin, string& s)
{
	s.clear();
	char c = cin.get();
	while (c != '\n')
	{
		s.append(c);
		c = cin.get();
	}
}