#pragma once
#include "same.hpp"

template <template <typename, typename> typename R>
struct relation
{
    template <typename T>
    using reflexive = R<T, T>;

    template <ttypename T, typename U>
    using coreflexive = IMPLY<R<T, U>, same<T, U>>;

    template <typename T, typename U>
    using symmetric = IMPLY<R<T, U>, R<U, T>>;

    template <typename T, typename U>
    using antisymmetric = IMPLY<AND<R<T, U>, R<U, T>>, same<T, U>>;

    template <typename T, typename U>
    using trichotomous = EQUAL<ADD<R<T, U>, R<U, T>, same<T, U>>, val<1>>;

    template <typename T, typename U>
    using total = OR<R<T, U>, R<U, T>>;

    template <typename T, typename U, typename V>
    using transitive = IMPLY<AND<R<T, U>, R<U, V>>, R<T, V>>;
};