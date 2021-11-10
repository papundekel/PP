#include "function_type.hpp"

#include <iostream>
#include <sstream>
#include <tuple>

PPtest::function_type test;

int main()
{
    std::stringstream out_key;
    std::stringstream out_run;

    test(out_key, out_run);

    auto view_key = out_key.view();
    auto view_run = out_run.view();

    if (view_key == view_run)
    {
        std::cout << "passed\n";
        return 0;
    }
    else
    {
        std::cout << "failed\n"
                  << "------\n"
                  << "key: |" << view_key << "|\n"
                  << "run: |" << view_run << "|\n"
                  << "------\n";
        return 1;
    }
}
