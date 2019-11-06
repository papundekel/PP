#pragma once
#include <initializer_list>
#include "forward.hpp"
#include "enable_if.hpp"
#include "is_iterator_bi.hpp"
#include "next.hpp"
#include "swap.hpp"
#include "conditional.hpp"
template <typename T>
class forward_list
{
	struct node;
	struct node_base
	{
		node_base* next;
		node_base(node_base* next)
			: next(next)
		{}
		virtual ~node_base()
		{
			delete dynamic_cast<node*>(next);
		}

		bool operator!=(const node_base& other)
		{
			return next != other.next;
		}
	};
	struct node : node_base
	{
		T object;

		node()
			: node_base(nullptr)
			: object()
		{}
		node(node_base* next)
			: node_base(next)
			, object()
		{}
		template <typename U>
		node(U&& object)
			: node_base(nullptr)
			, object(forward<U>(object))
		{}
		template <typename U>
		node(U&& object, node_base* next)
			: node_base(next)
			, object(forward<U>(object))
		{}
		node(const node&) = delete;
		node(node&&) = delete;
	};

	template <typename it>
	node_base* create(it begin, it end, node_base* append = nullptr)
	{
		static_assert(is_iterator<it>);

		if (begin != end)
		{
			if constexpr (is_iterator_bi<it>)
			{
				while (--end != begin)
					append = new node(*end, append);

				append = new node(*begin, append);
				return append;
			}
			else
			{
				node_base* first = new node(*begin);
				node_base* last = first;
				while (++begin != end)
				{
					last->next = new node(*begin);
					last = last->next;
				};
				last->next = append;
				return first;
			}
		}
		else
			return append;
	}

	node_base head;

public:
	forward_list()
		: head(nullptr)
	{}
	explicit forward_list(size_t count)
		: forward_list()
	{
		for (size_t i = 0; i != count; ++i)
			push_front();
	}
	forward_list(size_t count, const T & value)
		: forward_list()
	{
		for (size_t i = 0; i != count; ++i)
			push_front(value);
	}
	forward_list(size_t count, T(&g)())
		: head(new node(g()))
	{
		auto last = head;
		for (auto i = 1; i != count; ++i)
		{
			last->next = new node(g());
			last = last->next;
		};
	}
	forward_list(const std::initializer_list<T> & init_list)
		: head(create(init_list.begin(), init_list.end()))
	{}
	template <typename it>
	forward_list(it begin, it end)
		: head(create(begin, end))
	{}
	forward_list(const forward_list& copy)
		: head(create(copy.begin(), copy.end()))
	{}
	forward_list(forward_list && move)
		: head(move.head.next)
	{
		move.head.next = nullptr;
	}
	forward_list& operator=(const forward_list& right)
	{
		if (right.head != head)
		{
			delete[] head.next;
			head.next = create(right.begin(), right.end());
		}

		return *this;
	}
	forward_list& operator=(forward_list&& right)
	{
		if (right.head != head)
			swap(head.next, right.head.next);

		return *this;
	}
	template <bool is_const>
	class _iterator
	{
		using node_base_t = conditional<is_const, const node_base, node_base>;
		using node_t = conditional<is_const, const node, node>;

	public:
		node_base_t* ptr;

		_iterator(node_base_t* pointer)
			: ptr(pointer)
		{}

		auto* operator->()
		{
			return &dynamic_cast<node_t*>(ptr)->object;
		}
		auto& operator*()
		{
			return dynamic_cast<node_t*>(ptr)->object;
		}
		_iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		bool operator==(_iterator other)
		{
			return ptr == other.ptr;
		}
		friend bool operator!=(_iterator lhs, _iterator rhs)
		{
			return lhs.ptr != rhs.ptr;
		}
	};
	using iterator = _iterator<false>;
	using const_iterator = _iterator<true>;

	iterator begin()
	{
		return head.next;
	}
	const_iterator begin() const
	{
		return head.next;
	}
	iterator before_begin()
	{
		return &head;
	}
	const_iterator before_begin() const
	{
		return &head;
	}
	iterator end()
	{
		return nullptr;
	}
	const_iterator end() const
	{
		return nullptr;
	}
	iterator last()
	{
		return begin().last();
	}
	const_iterator last() const
	{
		return begin().last();
	}
	T& operator[](size_t index)
	{
		return begin()[index];
	}
	const T& operator[](size_t index) const
	{
		return begin()[index];
	}
	T& front()
	{
		return *begin();
	}
	const T& front() const
	{
		return *begin();
	}
	T& back()
	{
		return *last();
	}
	const T& back() const
	{
		return *last();
	}
	size_t count() const
	{
		return distance(begin(), end());
	}
	bool empty() const
	{
		return begin() == nullptr;
	}
	void clear()
	{
		delete head.next;
		head.next = nullptr;
	}
	void push_front()
	{
		head = new node(head);
	}
	template <typename U>
	void push_front(U&& var)
	{
		head.next = new node(std::forward<U>(var), head.next);
	}
	template <typename it>
	void push_front(it begin, it end)
	{
		head = create(begin, end, head);
	}
	void push_front(std::initializer_list<T> init_list)
	{
		push_front(init_list.begin(), init_list.end());
	}
private:
	void append(node_base * first)
	{
		last().next() = first;
	}
public:
	void push_back()
	{
		append(new node);
	}
	template <typename U>
	void push_back(U && var)
	{
		append(new node(std::forward<U>(var)));
	}
	template <typename it>
	void push_back(it begin, it end)
	{
		append(create(begin, end));
	}
	void push_back(std::initializer_list<T> init_list)
	{
		push_back(init_list.begin(), init_list.end());
	}
	void disconnect_after(iterator before_begin, iterator last)
	{
		if (!empty())
		{
			auto temp = next(last);
			last.ptr->next = nullptr;
			before_begin.ptr->next = temp.ptr;
		}
	}
	void disconnect_after(iterator where)
	{
		disconnect_after(where, next(where));
	}
	void erase_after(iterator before_begin, iterator last)
	{
		if (!empty())
		{
			auto temp = last.next();
			last.next() = nullptr;
			delete before_begin.next();
			before_begin.next() = temp;
		}
	}
	void erase_after(iterator where)
	{
		erase_after(where, where.next());
	}
	void erase(size_t index)
	{
		erase_after(before_begin() + index);
	}
	void pop_front()
	{
		erase_after(before_begin());
	}
	void pop_back()
	{
		if (!empty())
		{
			if (begin().next() == nullptr)
				clear();
			else
			{
				auto pred = before_begin();
				auto after = pred + 2;
				for (; after != end(); ++pred, ++after);
				delete pred.next();
				pred.next() = nullptr;
			}
		}
	}
	template <typename U>
	void insert_after(iterator where, U && var)
	{
		where.next() = new node(forward<U>(var), where.next());
	}
	template <typename it>
	void insert_after(iterator where, it begin, it end)
	{
		where.next() = create(begin, end, where.next());
	}
	void insert_after(iterator where, std::initializer_list<T> init_list)
	{
		insert_after(where, init_list.begin(), init_list.end());
	}
	template <typename U>
	void insert_after(size_t index, U && var)
	{
		insert_after(begin() + index, var);
	}
	template <typename it>
	void insert_after(size_t index, it begin, it end)
	{
		insert_after(this->begin() + index, begin, end);
	}
	void insert_after(size_t index, std::initializer_list<T> init_list)
	{
		insert_after(begin() + index, init_list);
	}
	void splice_after(iterator before_begin_dest, iterator before_begin_source, iterator last_source)
	{
		if (last_source.ptr)
		{
			auto temp = before_begin_source.next();
			before_begin_source.next() = last_source.next();
			last_source.next() = before_begin_dest.next();
			before_begin_dest.next() = temp;
		}
	}
	void splice_after(iterator before_begin_dest, iterator before_begin_source)
	{
		splice_after(before_begin_dest, before_begin_source, before_begin_source.last());
	}
	void splice_after(iterator before_begin_dest, forward_list<T> & source)
	{
		if (!source.empty())
			splice_after(before_begin_dest, source.before_begin());
	}
	void splice_one_after(iterator before_begin_dest, iterator before_begin_source)
	{
		splice_after(before_begin_dest, before_begin_source, next(before_begin_source));
	}
};