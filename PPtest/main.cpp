#include <iostream>

namespace PPtest
{
void zip_unbounded();
void vector();
void to_chars();
void conjunction();
void combine();
void add_const();
void tuple_any();
void tuple_apply();
void tuple_concat();
void tuple_fold();
void cout();
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
    std::pair<void (*)(), const char*> tests[] = {
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
        {PPtest::cout, "cout"},
    };

    for (auto [function, name] : tests)
    {
        std::cout << '|' << name << "|\n";
        print_many('-', std::char_traits<char>::length(name)) << "--\n";
        function();
        print_many('-', 80) << "\n";
    }

    return 0;
}
