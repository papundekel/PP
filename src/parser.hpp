#pragma once
#include <array>
#include "unique_ptr.hpp"
#include "move.hpp"
#include "list.hpp"
#include "big_int.hpp"
#include "range.hpp"
#include "contains.hpp"
#include "prev.hpp"
#include "next.hpp"
#include "remove_if.hpp"
#include <map>
#include "equal.hpp"

template <size_t s>
class expression_tree
{
	using B = big_int<s>;

	static constexpr std::array<char, 5> operators = { '+', '-', '*', '/', '%' };

	class index_out_of_range {};

	struct node
	{
		virtual B evaluate() = 0;
	};
	struct value_node : public node
	{
		B value;

		value_node(const B& value)
			: value(value)
		{}

		B evaluate() override
		{
			return value;
		}
	};
	struct variable_node : public node
	{
		const B& var;

		variable_node(const B& var)
			: var(var)
		{}

		B evaluate() override
		{
			return var;
		}
	};
	struct binary_node : public node
	{
		class unknown_operator {};

		unique_ptr<node> left;
		unique_ptr<node> right;
		char op;

		binary_node(unique_ptr<node>&& left, char op, unique_ptr<node>&& right)
			: left(move(left))
			, right(move(right))
			, op(op)
		{}

		B evaluate() override
		{
			switch (op)
			{
			case '+': return left->evaluate() + right->evaluate(); break;
			case '-': return left->evaluate() - right->evaluate(); break;
			case '*': return left->evaluate() * right->evaluate(); break;
			case '/': return left->evaluate() / right->evaluate(); break;
			case '%': return left->evaluate() % right->evaluate(); break;
			default: throw unknown_operator();
			}
		}
	};
	struct unary_node : public node
	{
		class unknown_operator {};

		unique_ptr<node> right;
		char op;

		unary_node(char op, unique_ptr<node>&& right)
			: right(move(right))
			, op(op)
		{}

		B evaluate() override
		{
			switch (op)
			{
			case '+': return  right->evaluate(); break;
			case '-': return -right->evaluate(); break;
			default: throw unknown_operator();
			}
		}
	};

	B variable;
	unique_ptr<node> first;

	template <typename it>
	static bool is_unary(it begin, it pos)
	{
		return pos == begin || contains(operators, *std::prev(pos));
	}

	template <typename it>
	static bool is_not_unary(it begin, it pos)
	{
		return !is_unary(begin, pos);
	}

	template <typename it>
	using _x = bool(*)(it, it);

	template <typename it>
	static constexpr _x<it> is_unary_arr[2] = { is_unary<it>, is_not_unary<it> };

	template <bool unary, typename it>
	static it find_last_of(range<it> r, const std::initializer_list<char>& ops)
	{
		auto old_end = r.end;

		for (size_t bracket_layer = 0; r.begin != r.end; --r.end)
		{
			auto before_end = prev(r.end);

			if (bracket_layer == 0 && contains(ops, *before_end) &&	is_unary_arr<it>[!unary](r.begin, before_end))
				return prev(r.end);
			else
			{
				if (*before_end == ')')
					++bracket_layer;
				else if (*before_end == '(')
					--bracket_layer;
			}
		}

		return old_end;
	}

	template <typename it>
	static inline it find_priority3(range<it> r)
	{
		return find_last_of<false>(r, { '+', '-' });
	}
	template <typename it>
	static inline it find_priority2(range<it> r)
	{
		return find_last_of<false>(r, { '*', '/', '%' });
	}
	template <typename it>
	static inline it find_priority1(range<it> r)
	{
		return find_last_of<true>(r, { '+', '-' });
	}

	template <typename it>
	unique_ptr<node> make_tree(range<it> r)
	{
		if (r.begin != r.end)
		{
			it old_begin;
			do
			{
				old_begin = r.begin;
				{
					range left(r, find_priority3(r));
					range right(r.end, r.end);
					if (left.end != r.end)
					{
						right.begin = next(left.end);
						return new binary_node(make_tree(left), *left.end, make_tree(right));
					}
					else
					{
						left.end = find_priority2(r);
						if (left.end != r.end)
						{
							right.begin = next(left.end);
							return new binary_node(make_tree(left), *left.end, make_tree(right));
						}
						else
						{
							left.end = find_priority1(r);
							if (left.end != r.end)
							{
								right.begin = next(left.end);
								return new unary_node(*left.end, make_tree(right));
							}
						}
					}
				}

				for (; *r.begin == '(' && *std::prev(r.end) == ')'; ++r.begin, --r.end);

			} while (r.begin != old_begin);
		}

		if (distance(r) == 1 && *r.begin == 'x')
			return new variable_node(variable);

		return new value_node(B(r, 10));
	}

public:
	template <typename it, typename = enable_if<is_iterator_bi<it>>>
	expression_tree(range<it> r, const B& b)
		: first(make_tree(range(r.begin, remove_if(r, isspace))))
		, variable(b)
	{}
	B evaluate()
	{
		return first->evaluate();
	}
};

template <size_t s, typename it>
auto inline parse(range<it> r, const big_int<s>& b)
{
	static_assert(is_iterator_bi<it>, "parse: iterator must be bi-directional");
	return expression_tree<s>(r, b).evaluate();
}