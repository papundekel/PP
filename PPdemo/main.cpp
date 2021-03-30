#include <iomanip>
#include <iostream>
#include <vector>
#include <variant>

#include "PP/any_iterator.hpp"
#include "PP/concepts/fundamental.hpp"
#include "PP/simple_vector.hpp"

class dynamic_reference
{
	friend class dynamic_object;

	std::variant<void*, void(*)()> ptr;
	const int* type_;

public:
	dynamic_reference(const dynamic_reference&) = default;

	constexpr dynamic_reference(const void* ptr, const int& t) noexcept
		: ptr(const_cast<void*>(ptr))
		, type_(&t)
	{}

private:
	template <typename Return, typename... Parameters>
	constexpr dynamic_reference(Return (*ptr)(Parameters...), const int& t) noexcept
		: ptr((void(*)())ptr)
		, type_(&t)
	{}

public:
	dynamic_reference& operator=(const dynamic_reference&) = default;

	struct bad_cast_exception {};

	constexpr const int& get_type() const noexcept
	{
		return *type_;
	}
};

void g(PP::any_iterator<PP::iterator_category::ra, dynamic_reference> i)
{
	std::cout << i->get_type() << "\n";
}

void f(PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&> i)
{
	g(i);
}

int main()
{
	int a = 7;

	PP::simple_vector<dynamic_reference> rs;
	rs.push_back(nullptr, a);

	f(PP::make_any_iterator(PP::view_begin(rs)));

	std::cout.flush();
	return 0;
}
