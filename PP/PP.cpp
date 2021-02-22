#include <iostream>
#include <vector>

#include "dynamic_block.hpp"
#include "tuple_apply.hpp"
#include "tuple_fold.hpp"
#include "tuple_map.hpp"
#include "tuple_zip_indices.hpp"
#include "tuple_prepend.hpp"
#include "tuple_make.hpp"
#include "tuple_splits.hpp"
#include "unique_pointer.hpp"
#include "singular_tuple.hpp"
#include "tuple_concat.hpp"
#include "tuple_find_get.hpp"
#include "view_equal.hpp"
#include "simple_vector.hpp"
#include "string_view.hpp"

struct Abstract
{
	virtual void f() const = 0;

	virtual ~Abstract()
	{}
};

struct Derived : public Abstract
{
	int x;
	bool zivy;

	Derived(int x)
		: x(x)
		, zivy(true)
	{}
	Derived(Derived&& other)
		: x(other.x)
		, zivy(other.zivy)
	{
		other.zivy = false;
	}

	void f() const override final
	{
		std::cout << x << '\n';
	}


	~Derived()
	{
		if (zivy)
			std::cout << "som umar " << x << "\n";
	}
};

PP::string_view f(const PP::simple_vector<char>& v)
{
	return v;
}

int main()
{
	using namespace PP::literals;

	[[maybe_unused]] auto v = "operator int"_sv;

	[[maybe_unused]] PP::simple_vector<char> s(v);

	[[maybe_unused]] auto x = f(s);

	std::cout.flush();
	return 0;
}
