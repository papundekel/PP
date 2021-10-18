#include "PPtest.hpp"

#include "PP/view/lower_bound.hpp"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

namespace PPtest
{
std::ostream& operator<<(std::ostream& out, std::strong_ordering order)
{
    if (order == std::strong_ordering::less)
        out << "l";
    else if (order == std::strong_ordering::equal)
        out << "E";
    else if (order == std::strong_ordering::equivalent)
        out << "e";
    else if (order == std::strong_ordering::greater)
        out << "g";

    return out;
}

namespace
{
void g(std::ostream& out,
       int a,
       auto& i,
       std::strong_ordering order,
       auto& numbers)
{
    out << a << ", ";

    if (i == numbers.end())
        out << "end";
    else
        out << *i;

    out << ": " << order << ". ";
}

void f(std::ostream& out_key, std::ostream& out_run, int a, auto& numbers)
{
    auto [i_run, order] = PP::view::lower_bound(numbers, a);
    g(out_run, a, i_run, order, numbers);

    auto i_key = std::lower_bound(numbers.begin(), numbers.end(), a);
    g(out_key,
      a,
      i_key,
      (i_key == numbers.end() ? std::strong_ordering::less : (*i_key <=> a)),
      numbers);
}
}

template<> std::string_view test_function_name<3>() { return __FILE__; }

template<>
void test_function<3>(std::ostream& out_key, std::ostream& out_run)
{
    std::srand(std::time(nullptr));

    int size = std::rand();
    if (size < 0)
        size = -size;
    size %= 10;
    size += 10;

    std::vector<int> numbers;

    for (int i = 0; i != size; ++i)
        numbers.push_back(std::rand());
    std::sort(numbers.begin(), numbers.end());

    auto f_applied = [&out_key, &out_run, &numbers](int a)
    {
        f(out_key, out_run, a, numbers);
    };

    for (int i = 0; i != 3; ++i)
        f_applied(std::rand());

    for (auto e : numbers)
        f_applied(e);

    f_applied(numbers.back() + 1);
}
}
