#pragma once
#include <PP/apply_transform.hpp>
//#include <PP/arg_splitter.hpp>
#include <PP/arrow_operator_wrapper.hpp>
#include <PP/compressed_pair.hpp>
#include <PP/concepts/pointer.hpp>
#include <PP/decompose_template.hpp>
#include <PP/get_type.hpp>
#include <PP/in_place_tag.hpp>
#include <PP/iterator_inner.hpp>
#include <PP/ptrdiff_t.hpp>
#include <PP/remove_cvref.hpp>
#include <PP/view/pair.hpp>

namespace PP
{
// constexpr inline struct transform_iterator_in_place_delimiter_t
// {
// } transform_iterator_in_place_delimiter;

template <typename BaseIterator, typename Transform>
class transform_iterator
{
    // static constexpr auto splitter = arg_splitter *
    // type<transform_iterator_in_place_delimiter_t> *
    // type_tuple<BaseIterator, Transform>;

    compressed_pair<BaseIterator, Transform> iterator_transform;

public:
    constexpr transform_iterator(auto&& iterator, auto&& transform)
        : iterator_transform(PP_F(iterator), PP_F(transform))
    {}
    // constexpr transform_iterator(in_place_tag_t, auto&&... args)
    //	: iterator_transform
    //	(
    //		splitter(value_0, PP_F(args)...),
    //		splitter(value_1, PP_F(args)...)
    //	)
    //{}

    constexpr decltype(auto) operator*() const
    {
        return iterator_transform.second(*iterator_transform.first);
    }
    constexpr auto operator->() const
    {
        return make_arrow_operator_wrapper(
            [this]()
            {
                return **this;
            });
    }
    constexpr void step()
    {
        ++iterator_transform.first;
    }
    constexpr auto step_back()
    {
        if constexpr (PP::concepts::iterator_bi<BaseIterator>)
            --iterator_transform.first;
        else
            return 0;
    }
    constexpr auto advance(ptrdiff_t offset)
    {
        if constexpr (PP::concepts::iterator_ra<BaseIterator>)
            iterator_transform.first += offset;
        else
            return 0;
    }
    constexpr auto operator==(const auto& other) const
    {
        return iterator_transform.first == PP::iterator_inner(other);
    }
    constexpr auto operator-(const transform_iterator& other) const
    {
        if constexpr (PP::concepts::iterator_ra<BaseIterator>)
            return iterator_transform.first - other.iterator_transform.first;
        else
            return ptrdiff_t(0);
    }
    constexpr auto operator-(const auto& other) const
    {
        return iterator_transform.first - PP::iterator_inner(other);
    }
    constexpr decltype(auto) operator[](ptrdiff_t offset) const
    {
        if constexpr (PP::concepts::iterator_ra<BaseIterator>)
            return iterator_transform.second(iterator_transform.first[offset]);
    }
    constexpr auto inner_iterator() const
    {
        return iterator_transform.first;
    }
};
template <typename I, typename T>
transform_iterator(I&& i, T&& t)
    -> transform_iterator<PP_GT(~type<I>), PP_GT(~type<T>)>;

template <typename Functor>
struct transform
{
    Functor functor;
};

constexpr auto transform_view(concepts::view auto&& v, auto&& f)
{
    return transform_iterator(view::begin_(PP_F(v)), PP_F(f)) ^
           transform_iterator(view::end_(PP_F(v)), PP_F(f));
}
}

constexpr auto operator&(PP::concepts::iterator auto&& i, PP::transform<auto> t)
{
    return PP::transform_iterator(PP_F(i), PP::move(t).functor);
}

constexpr auto operator|(PP::concepts::view auto&& v, PP::transform<auto> t)
{
    return PP::transform_view(PP_F(v), PP::move(t).functor);
}
