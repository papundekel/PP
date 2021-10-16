#include <iostream>
#include <sstream>

namespace PPtest
{
using test_function_type = void(std::ostream& out_key, std::ostream& out_run);

test_function_type zip_unbounded;
test_function_type vector;
test_function_type to_chars;
test_function_type conjunction;
test_function_type combine;
test_function_type add_const;
test_function_type tuple_any;
test_function_type tuple_apply;
test_function_type tuple_concat;
test_function_type tuple_fold;
test_function_type ostream_std;
test_function_type view_subsequence;
}

namespace
{
auto& print_many(char c, std::size_t count)
{
    for (auto i = 0z; i != count; ++i)
        std::cout << c;
    return std::cout;
}
}

int main()
{
    std::pair<PPtest::test_function_type&, const char*> tests[] = {
        {PPtest::zip_unbounded, "zip_unbounded"},
        {PPtest::vector, "vector"},
        {PPtest::to_chars, "to_chars"},
        {PPtest::combine, "combine"},
        {PPtest::conjunction, "conjunction"},
        {PPtest::add_const, "add_const"},
        {PPtest::tuple_any, "tuple_any"},
        {PPtest::tuple_apply, "tuple_apply"},
        {PPtest::tuple_concat, "tuple_concat"},
        {PPtest::tuple_fold, "tuple_fold"},
        {PPtest::ostream_std, "ostream_std"},
        {PPtest::view_subsequence, "view_subsequence"},
    };

    std::size_t count_passed = 0;

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

            std::cout << view_key.size() << " " << view_run.size() << "\n";

            auto i = std::begin(view_key);
            auto j = std::begin(view_run);

            for (; i != std::end(view_key) && j != std::end(view_run); ++i, ++j)
            {
                if (*i != *j)
                    std::cout << "<" << (int)*i << "/" << (int)*j << ">";
                else
                    std::cout << *i;
            }
            std::cout << "\n";
        }
    }

    std::cout << "Tests passed: " << count_passed << "/" << std::size(tests);

    return count_passed == std::size(tests) ? 0 : 1;
}
