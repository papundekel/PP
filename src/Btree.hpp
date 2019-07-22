#pragma once
#include "int.hpp"
#include "list.hpp"
template <typename T>
class Btree
{
	struct node
	{
		size_t order;
		node* parent;
		list<T> values;
		list<node*> children;
		bool leaf()
		{
			return children.empty();
		}
		bool full()
		{
			return values.count() == order;
		}
		node(size_t o, node* p)
			: order(o)
			, parent(p)
			, values(order)
			, children(order + 1)
		{}
		size_t get_value_i(const T& value)
		{
			size_t i = 0;
			for (; i != order && values[i] < value; ++i);
			return i;
		}
		node* get_child(const T & value)
		{
			size_t i = 0;
			for (; i != order && values[i] < value; ++i);
			return children[i];
		}
		template <typename U>
		auto insert(U&& value)
		{
			auto i = values.begin();
			for (; *i < value; ++i);
			values.insert(i, forward<U>(value));
			return i;
		}
		node* split()
		{
			auto left = new node(order, this);
			auto right = new node(order, this);
			left->values.insert(0, range(values.begin(), values(order / 2)));
			left->children.insert(0, range(children.begin(), children(order / 2 + 1)));
			right->values.insert(0, range(values(order / 2 + 1), values.end()));
			right->children.insert(0, range(children(order / 2 + 1), children.end()));

			if (parent)
			{
				parent->insert(values[order / 2]);
				size_t i = parent->get_value_i(values[order / 2]);

				return parent;
			}
			else
				return this;
		}

	};

	size_t order;
	node* root;
public:
	Btree(size_t o)
		: order(o)
		, root(new node(order, nullptr))
	{}

	template <typename U>
	auto insert(U&& value)
	{
		auto i = root;
		while (i->full())
		{
			i = i->split();
			i = i->get_child(value);
		}
		i->insert(forward<U>(value));
	}
};