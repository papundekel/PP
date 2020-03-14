#pragma once
#include "forward.hpp"
#include "conditional.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "remove_const.hpp"

template <typename T>
class linked_list
{
	struct node;
	struct node_base
	{
		node_base* prev;
		node_base* next;
		node_base(node_base* prev, node_base* next)
			: prev(prev)
			, next(next)
		{}
		virtual ~node_base()
		{
			delete dynamic_cast<node*>(next);
		}

		bool operator!=(const node_base& other)
		{
			return prev != other.prev || next != other.next;
		}
	};
	struct node : public node_base
	{
		T object;

		node()
			: node_base(nullptr)
			, object()
		{}
		node(node_base* prev, node_base* next)
			: node_base(prev, next)
			, object()
		{}
		template <typename U>
		node(U&& object)
			: node_base(nullptr)
			, object(forward<U>(object))
		{}
		template <typename U>
		node(U&& object, node_base* prev, node_base* next)
			: node_base(prev, next)
			, object(forward<U>(object))
		{}
		node(const node&) = delete;
		node(node&&) = delete;
	};

	template <typename it, typename it_end>
	pair<node_base*> create(range<it, it_end> r)
	{
		static_assert(is_iterator<it>);

		if (r.begin != r.end)
		{
			auto i = new node(*r.begin, &head, &tail);
			pair<node_base*> result(i, i);

			for (; ++r.begin != r.end;)
			{
				result.second = new node(*r.begin, result.second, &tail);
				result.second->prev->next = result.second;
			}
			return result;
		}
		else
			return { nullptr, nullptr };
	}

	node_base head;
	node_base tail;
	linked_list(pair<node_base*> first_last)
		: head(nullptr, first_last.first)
		, tail(first_last.second, nullptr)
	{}

	class const_iterator
	{
	public:
		node_base* ptr;

		const_iterator(node_base* ptr)
			: ptr(ptr)
		{}

		auto operator->()
		{
			return &(dynamic_cast<const node*>(ptr)->object);
		}
		auto& operator*()
		{
			return dynamic_cast<const node*>(ptr)->object;
		}
		const_iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		const_iterator& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}
		bool operator==(const_iterator other)
		{
			return ptr == other.ptr;
		}
		bool operator!=(const_iterator other)
		{
			return ptr != other.ptr;
		}
	};
	class iterator : public const_iterator
	{
	public:
		iterator(node_base* ptr)
			: const_iterator(ptr)
		{}

		auto operator->()
		{
			return const_cast<remove_const<decltype(const_iterator::operator->())>>(const_iterator::operator->());
		}
		auto& operator*()
		{
			return const_cast<remove_const<decltype(const_iterator::operator*())>>(const_iterator::operator*());
		}
	}

public:
	linked_list()
		: linked_list({ &tail, &head })
	{}
	template <typename it, typename it_end>
	linked_list(range<it, it_end> r)
		: linked_list(create(r))
	{}

	using riterator = reverse_iterator<iterator>;
	using rconst_iterator = reverse_iterator<const_iterator>;

	iterator begin()
	{
		return head.next;
	}
	const_iterator before_begin()
	{
		return &head;
	}
	const_iterator before_begin() const
	{
		return &head;
	}
	const_iterator begin() const
	{
		return head.next;
	}
	iterator end()
	{
		return &tail;
	}
	const_iterator end() const
	{
		return &tail;
	}
	riterator rbegin()
	{
		return tail.prev;
	}
	rconst_iterator rbefore_begin()
	{
		return &tail;
	}
	rconst_iterator rbefore_begin() const
	{
		return &tail;
	}
	rconst_iterator rbegin() const
	{
		return tail.prev;
	}
	riterator rend()
	{
		return &head;
	}
	rconst_iterator rend() const
	{
		return &head;
	}
};