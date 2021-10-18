#include "PPtest.hpp"

#include "PP/vector.hpp"

#include <iostream>
#include <vector>
#include <ctime>

namespace PPtest
{
namespace
{
    void f(std::ostream& out, auto& v)
    {
        for (int e : v)
            out << e << ", ";
    }

    int destructor_count;

    struct noisy
    {
        int val;

        operator int() const
        {
            return val;
        }

        ~noisy()
        {
            ++destructor_count;
        }
    };
}

template<> std::string_view test_function_name<10>() { return __FILE__; }

template<>
void test_function<10>(std::ostream& out_key, std::ostream& out_run)
{
    std::vector<int> v_key;
    PP::vector<noisy> v_run;

    int capacity = v_run.capacity();

    std::srand(std::time(nullptr));

    for (int i = 0; i != capacity + 1; ++i)
        v_key.push_back(std::rand());
    
    f(out_key, v_key);
    out_key << capacity;
    //
    destructor_count = 0;

    for (const auto& e : v_key)
        v_run.push_back(e);

    f(out_run, v_run);
    out_run << destructor_count;
}
}
