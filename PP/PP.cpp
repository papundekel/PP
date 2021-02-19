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

struct Abstract
{
	virtual void f() const = 0;

	virtual ~Abstract()
	{
		std::cout << "som umar\n";
	}
};

struct Derived : public Abstract
{
	int x;

	constexpr Derived(int x)
		: x(x)
	{}

	void f() const override final
	{
		std::cout << x << '\n';
	}
};

int main()
{
	{
		PP::unique_pointer<PP::pointer_new<Abstract>> p = PP::make_unique_pointer(PP::unique_tag_new, PP::type<Derived>, 5);

		p->f();
	}

	std::cout.flush();
	return 0;
}
