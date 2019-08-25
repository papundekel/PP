#pragma once
#include "same.hpp"
template <template <typename> typename MakeTrait>
struct trait_test
{
    template <typename T>
    using projective = same<MakeTrait<T>, MakeTrait<MakeTrait<T>>>;
};