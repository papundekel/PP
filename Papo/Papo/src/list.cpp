#include "list.hpp"
#include <cstring>
#include "sentinel.hpp"

list<bool>::list()
	: m_count(0)
	, m_block(2)
{}
list<bool>::list(size_t count)
	: m_count(count)
	, m_block(fit_count())
{}
list<bool>::list(size_t count, bool value)
	: m_count(count)
	, m_block(fit_count())
{
	int t;
	value ? t = -1 : t = 0;
	memset(m_block(0), t, m_block.count());
}
list<bool>::list(const list<bool>& other)
	: m_count(other.count())
	, m_block(fit_count())
{
	copy(range(other), range(*this));
}
list<bool>::list(list<bool>&& other) noexcept
	: m_count(other.m_count)
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
	return bit(m_count);
}
list<bool>::const_iterator list<bool>::end() const
{
	return bit(m_count);
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
	return bit(m_count - 1);
}
const bit_ref list<bool>::last() const
{
	return bit(m_count - 1);
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
	if (8 * m_count == m_block.count())
	{
		block<unsigned char> new_block(2 * m_block.count());
		copy(range(*this), range(bit_it({ new_block(0), 0 }), infinity()));
		m_block = move(new_block);
	}
	++m_count;
	last() = value;
}
void list<bool>::pop_back()
{
	--m_count;
}

const unsigned char* list<bool>::data() const
{
	return m_block(0);
}
size_t list<bool>::count() const
{
	return m_count;
}
size_t list<bool>::size() const
{
	return m_block.count();
}
size_t list<bool>::capacity() const
{
	return size() * byte_size;
}