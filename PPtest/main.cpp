#include <iostream>

namespace PPtest
{
void zip_unbounded();
void vector();
void to_chars();
}

int main()
{
    std::pair<void (*)(), const char*> tests[] = {
        {PPtest::zip_unbounded, "zip_unbounded"},
        {PPtest::vector, "vector"},
        {PPtest::to_chars, "to_chars"}};

    for (auto [function, name] : tests)
    {
        std::cout << name << ":\n"
                  << "----\n";
        function();
        std::cout << "----\n";
    }

    return 0;
}
