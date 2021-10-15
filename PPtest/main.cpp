#include <iostream>

#include "PP/containers/array.hpp"
#include "PP/ref_wrap.hpp"
#include "PP/transform_view.hpp"
#include "PP/vector.hpp"

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
    };

    for (auto [function, name] : tests)
    {
        std::cout << name << ":\n"
                  << "----\n";
        function();
        std::cout << "----\n";
    }

    std::string a = "abc", b = "defg";

    auto x = PP::array::forward(a, b);

    for (const auto& e : x)
        std::cout << e << ' ';

    PP::vector<PP::ref_wrap<std::string&>> strings(x);

    auto i = PP::view::begin_(strings) &
             PP::transform(PP::static__cast * PP::type<std::string&>);

    std::cout << PP::concepts::iterator<decltype(i)>;

    for (auto&& s :
         strings | PP::transform(PP::static__cast * PP::type<std::string&>))
        std::cout << s << ' ';

    return 0;
}
