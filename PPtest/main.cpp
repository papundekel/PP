#include "PPtest.hpp"

#include <iostream>
#include <sstream>
#include <tuple>

namespace
{
auto& print_many(char c, std::size_t count)
{
    for (auto i = 0z; i != count; ++i)
        std::cout << c;
    return std::cout;
}

std::string_view clean_name(std::string_view name)
{
    name.remove_suffix(4);

    std::string_view test_dir_name = "/PPtest/";

    return name.substr(name.rfind(test_dir_name) + test_dir_name.length());
}

template <std::size_t... I>
void fill_tests(auto& pairs, std::index_sequence<I...>)
{
    ((pairs[I].first = PPtest::test_function<I>,
      pairs[I].second = clean_name(PPtest::test_function_name<I>())),
     ...);
}
}

int main()
{
    using namespace PPtest;

    constexpr auto test_count = 13z;

    std::pair<test_function_type*, std::string_view> tests[test_count];

    fill_tests(tests, std::make_index_sequence<test_count>{});

    auto count_passed = 0z;

    for (auto [function, name] : tests)
    {
        std::cout << name << ": ";

        std::stringstream out_key;
        std::stringstream out_run;

        function(out_key, out_run);

        auto view_key = out_key.view();
        auto view_run = out_run.view();

        if (view_key == view_run)
        {
            std::cout << "passed\n";
            ++count_passed;
        }
        else
        {
            std::cout << "failed\n"
                      << "------\n"
                      << "key: |" << view_key << "|\n"
                      << "run: |" << view_run << "|\n"
                      << "------\n";
        }
    }

    std::cout << "Tests passed: " << count_passed << "/" << std::size(tests)
              << "\n";

    return count_passed == std::size(tests) ? 0 : 1;
}
