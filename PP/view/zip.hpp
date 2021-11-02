#pragma once
#include "../applier.hpp"
#include "../concepts/same_except_cvref.hpp"
#include "../construct_pack.hpp"
#include "../containers/tuple.hpp"
#include "../containers/tuple_std.hpp"
#include "../operators.hpp"
#include "../partial.hpp"
#include "../tuple/all.hpp"
#include "../tuple/any.hpp"
#include "../tuple/for_each.hpp"
#include "../tuple/map.hpp"
#include "../tuple/zip_with.hpp"
#include "concept.hpp"
#include "pair.hpp"

namespace PP::view
{
template <typename... Iterators>
class zip_iterator : public tuple::container<Iterators...>
{
    template <typename...>
    friend class zip_iterator;

public:
    static constexpr char dont_make_array_star_operator{};

    constexpr zip_iterator(placeholder_t, auto&&... iterators)
        : tuple::container<Iterators...>(placeholder, PP_F(iterators)...)
    {}

    constexpr auto operator*() const
    {
        if constexpr ((concepts::iterator<Iterators> && ...))
            return der + *this;
        else
            return 0;
    }
    constexpr void step()
    {
        if constexpr ((concepts::iterator<Iterators> && ...))
            tuple::for_each(ipr, *this);
    }
    constexpr auto advance(ptrdiff_t offset)
    {
        if constexpr ((concepts::iterator_ra<Iterators> && ...))
            tuple::for_each(partial(pas, value_1, offset), *this);
        else
            return 0;
    }
    template <typename... IteratorsOther>
    requires(sizeof...(Iterators) == sizeof...(IteratorsOther)) constexpr bool
    operator==(const zip_iterator<IteratorsOther...>& other) const noexcept
    {
        return eql++ || tuple::zip_pack(*this, other);
    }
};
template <typename... Iterators>
zip_iterator(placeholder_t, Iterators...) -> zip_iterator<Iterators...>;

PP_CIA make_zip_iterator = [](auto&&... iterators)
{
    return zip_iterator(placeholder, PP_F(iterators)...);
};

PP_CIA zip_pack = [](concepts::view auto&&... views)
{
    return pair(make_zip_iterator(begin_(PP_F(views))...),
                make_zip_iterator(end_(PP_F(views))...));
};
}
