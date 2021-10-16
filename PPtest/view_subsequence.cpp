#include <iostream>

#include "PP/view/subsequence.hpp"

namespace PPtest
{
namespace
{
auto f(auto& sub)
{
    static int arr[] = {1, 2, 3, 4, 5, 6};

    return (int)PP::view::subsequence(sub, arr);
}
}
void view_subsequence(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "0 0 1 2";
    //
    int sub[] = {1, 3, 4};
    int sub_cont[] = {3, 4, 5};
    int sub_equal[] = {1, 2, 3, 4, 5, 6};
    int non_sub[] = {1, 4, 3};

    out_run << f(sub) << ' ' << f(sub_cont) << ' ' << f(sub_equal) << ' '
            << f(non_sub);
}
}
