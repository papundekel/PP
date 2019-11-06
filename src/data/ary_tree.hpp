#pragma once
#include "range.hpp"
#include "list.hpp"

/*template <typename T, size_t arity = 0>
class ary_tree
{
	class base_node
	{
	public:
		virtual void add_child(const T& value) = 0;
		virtual bool full() = 0;
		virtual void repair() = 0;
		virtual base_node* get_parent() = 0;
	};

	class node : public base_node
	{
	public:
		T value;
		base_node* parent;
		list<base_node*> children;

		node(const T& value, base_node* parent)
			: value(value)
			, parent(parent)
			, children(arity)
		{}

		void add_child(const T& value) override
		{
			children.push_back(new node(value, this));
		}

		bool full() override
		{
			return children.count() == arity;
		}

		void repair() override
		{

		}

		base_node* get_parent()
		{

		}
	};

	class head_node : public base_node
	{
	public:
		node* root;

		void add_child(const T& value) override
		{
			root = new node(value, this);
		}

		bool full() override
		{
			return root;
		}

		void repair() override
		{

		}

		base_node* get_parent()
		{
			return nullptr;
		}
	};
public:
	head_node head;

	void insert(const T& value)
	{
		get_end()->add_child(value);
	}

	base_node* get_end()
	{
		base_node* i = &head;

		while (i->full())
		{
			
		}
	}
};

template <typename T>
class ary_tree<T, 0>
{

};*/