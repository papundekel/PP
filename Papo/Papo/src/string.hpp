#pragma once
#include "iterator_random_access.hpp"
#include "distance.hpp"
#include "copy.hpp"
#include <ostream>

class string
{
	size_t m_length;
	size_t m_capacity;
	char* m_buffer;

	string& _append(const char* buffer, size_t length);
	string _plus(const char* buffer, size_t length) const;
public:
	string();
	explicit string(size_t length);
	string(size_t count, char c);
	string(const char* ptr);
	string(const char* const ptr, size_t length);
	template <typename it>
	string(it begin, it end)
		: m_length(distance(begin, end))
		, m_capacity(m_length + 1)
		, m_buffer(new char[m_capacity])
	{
		copy(begin, end, m_buffer);
	}
	string(const string& copy);
	string(string&& move) noexcept;
	~string();

	string& operator=(const string& other);
	string& operator=(string&& other) noexcept;

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
	bool operator==(const string& other) const;
	bool operator!=(const char* other) const;
	bool operator!=(const string& other) const;

	string& append(char c);
	string& append(const char* const other);
	string& append(const string& other);
	string& operator+=(char c);
	string& operator+=(const char* other);
	string& operator+=(const string& other);

	string operator+(const char* const right) const;
	string operator+(const string& right) const;
	friend string operator+(const char* const left, const string& right);

	friend std::ostream& operator<<(std::ostream& cout, const string& str);

	static size_t length(const char* cstring);
};

string to_string(int x);

void getline(std::istream& cin, string& s);