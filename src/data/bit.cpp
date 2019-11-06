#include "bit.hpp"

bit_ptr::bit_ptr(const void* ptr, size_t offset)
	: byte(const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(ptr) + offset / byte_size))
	, offset(static_cast<unsigned char>(offset))
{}
bit_ptr& bit_ptr::operator++()
{
	++offset;
	if (offset == 0)
		++byte;
	return *this;
}
bit_ptr bit_ptr::operator++(int)
{
	auto temp = *this;
	--(*this);
	return temp;
}
bit_ptr& bit_ptr::operator--()
{
	if (offset == 0)
		--byte;
	--offset;
	return *this;
}
bit_ptr bit_ptr::operator--(int)
{
	auto temp = *this;
	--(*this);
	return temp;
}
bit_ptr bit_ptr::operator+(diff_t diff) const
{
	return bit_ptr(byte + ((diff + offset) >> byte_size_bits), offset + diff);
}
bit_ptr bit_ptr::operator-(diff_t diff) const
{
	return bit_ptr(byte - ((diff - offset) >> byte_size_bits), offset - diff);
}
diff_t bit_ptr::operator-(bit_ptr bit) const
{
	return 8 * (byte - bit.byte) + offset - bit.offset;
}
bool bit_ptr::operator==(bit_ptr bit) const
{
	return byte == bit.byte && offset == bit.offset;
}
bool bit_ptr::operator!=(bit_ptr bit) const
{
	return byte != bit.byte || offset != bit.offset;
}
bool bit_ptr::operator<(bit_ptr bit) const
{
	return byte == bit.byte ? offset < bit.offset : byte < bit.byte;
}

bit_ref::bit_ref(bit_ptr bit)
	: bit(bit)
{}
bit_ref::bit_ref(const bit_ref& copy)
	: bit(copy.bit)
{}
bit_ref::bit_ref(bit_ref&& move) noexcept
	: bit(move.bit)
{
	move.bit = bit_ptr(nullptr, 0);
}
bit_ref::operator bool() const
{
	return (*bit.byte >> bit.offset) & 1;
}
bit_ref bit_ref::operator=(bool value)
{
	*bit.byte ^= (-!!value ^ *bit.byte) & (1 << bit.offset);
	return *this;
}
bit_ref& bit_ref::operator=(const bit_ref& value)
{
	*this = static_cast<bool>(value);
	return *this;
}
bit_ref& bit_ref::operator=(bit_ref&& value) noexcept
{
	*this = static_cast<bool>(value);
	return *this;
}
bool bit_ref::operator==(const bit_ref& other) const
{
	return static_cast<bool>(*this) == static_cast<bool>(other);
}
bool bit_ref::operator!=(const bit_ref& other) const
{
	return static_cast<bool>(*this) != static_cast<bool>(other);
}

bit_it::bit_it(bit_ptr bit)
	: bit(bit)
{}
bit_ref bit_it::operator*() const
{
	return bit;
}
bit_ref bit_it::operator[](diff_t offset) const
{
	return bit + offset;
}
bit_it& bit_it::operator++()
{
	++bit;
	return *this;
}
bit_it bit_it::operator++(int)
{
	auto temp = *this;
	++bit;
	return temp;
}
bit_it& bit_it::operator--()
{
	--bit;
	return *this;
}
bit_it bit_it::operator--(int)
{
	auto temp = *this;
	--bit;
	return temp;
}
bit_it bit_it::operator+(diff_t other) const
{
	return bit + other;
}
bit_it bit_it::operator-(diff_t other) const
{
	return bit - other;
}
diff_t bit_it::operator-(bit_it other) const
{
	return bit - other.bit;
}
bool bit_it::operator==(bit_it other) const
{
	return bit == other.bit;
}
bool bit_it::operator!=(bit_it other) const
{
	return bit != other.bit;
}
bool bit_it::operator<(bit_it other) const
{
	return bit < other.bit;
}

const_bit_it::const_bit_it(bit_ptr bit)
	: bit(bit)
{}
const bit_ref const_bit_it::operator*() const
{
	return bit;
}
const bit_ref const_bit_it::operator[](diff_t offset) const
{
	return bit + offset;
}
const_bit_it& const_bit_it::operator++()
{
	++bit;
	return *this;
}
const_bit_it const_bit_it::operator++(int)
{
	auto temp = *this;
	++bit;
	return temp;
}
const_bit_it& const_bit_it::operator--()
{
	--bit;
	return *this;
}
const_bit_it const_bit_it::operator--(int)
{
	auto temp = *this;
	--bit;
	return temp;
}
const_bit_it const_bit_it::operator+(diff_t other) const
{
	return bit + other;
}
const_bit_it const_bit_it::operator-(diff_t other) const
{
	return bit - other;
}
diff_t const_bit_it::operator-(const_bit_it other) const
{
	return bit - other.bit;
}
bool const_bit_it::operator==(const_bit_it other) const
{
	return bit == other.bit;
}
bool const_bit_it::operator!=(const_bit_it other) const
{
	return bit != other.bit;
}
bool const_bit_it::operator<(const_bit_it other) const
{
	return bit < other.bit;
}