#pragma once
template <typename T>
class optional
{
	bool _has_value;
	union {
		mutable unsigned char memory[sizeof(T)];
		mutable T value;
	};

public:

	optional()
		: _has_value(false)
		, memory()
	{}
	optional(const optional& other)
		: _has_value(other._has_value)
	{
		if (_has_value)
			new (memory) T(*other);
	}
	optional(optional&& other)
		: _has_value(other._has_value)
	{
		if (_has_value)
			new (memory) T(move(other));
	}
	template <typename U>
	optional(U&& value)
		: _has_value(true)
	{
		static_assert(is_convertible<U, T>, "optional: U must be convertible to T");
		new (memory) T(forward<U>(value));
	}
	void reset()
	{
		if (_has_value)
		{
			value.~T();
			_has_value = false;
		}
	}
	~optional()
	{
		if (_has_value)
			value.~T();
	}
	explicit operator bool() const
	{
		return _has_value;
	}
	bool has_value() const
	{
		return _has_value;
	}
	T* operator->()
	{
		return memory;
	}
	const T* operator->() const
	{
		return memory;
	}
	T& operator*() &
	{
		return value;
	}
	T&& operator*() &&
	{
		return move(value);
	}
	const T& operator*() const&
	{
		return value;
	}
	const T&& operator*() const&&
	{
		return move(*value);
	}
	template <typename U>
	T value_or(U&& _value) const&
	{
		static_assert(is_convertible<U, T>, "optional: U must be convertible to T");
		if (_has_value)
			return value;
		else
			return forward<U>(_value);
	}
	template <typename U>
	T value_or(U&& _value) &&
	{
		static_assert(is_convertible<U, T>, "optional: U must be convertible to T");
		if (_has_value)
			return move(value);
		else
			return forward<U>(_value);
	}
};