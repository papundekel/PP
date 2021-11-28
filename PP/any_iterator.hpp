#pragma once
#include <PP/always_false.hpp>
#include <PP/apply_transform.hpp>
#include <PP/arrow_operator_wrapper.hpp>
#include <PP/concepts/atomic/returnable.hpp>
#include <PP/concepts/constructible.hpp>
#include <PP/concepts/convertible_to.hpp>
#include <PP/concepts/reference.hpp>
#include <PP/concepts/same_except_cvref.hpp>
#include <PP/construct_pack.hpp>
#include <PP/containers/tuple_std.hpp>
#include <PP/empty.hpp>
#include <PP/get_reference.hpp>
#include <PP/ptrdiff_t.hpp>
#include <PP/tuple/find_dynamic.hpp>
#include <PP/tuple/get_dynamic.hpp>
#include <PP/tuple/prepend.hpp>
#include <PP/unique_pointer.hpp>
#include <PP/utility/move.hpp>
#include <PP/value_t.hpp>
#include <PP/view/empty.hpp>
#include <PP/view/pair.hpp>

#include <memory>

namespace PP
{
enum class iterator_category : int
{
    fw,
    bi,
    ra,
};
}

constexpr bool operator<=(PP::iterator_category a, PP::iterator_category b)
{
    return (int)a <= (int)b;
}
constexpr PP::iterator_category operator-(PP::iterator_category a)
{
    return PP::iterator_category((int)a - 1);
}

namespace PP
{
PP_CIA add_cv_reference = [](concepts::value auto&& cv, concepts::type auto&& t)
{
    return add_reference(get_reference_value_t(t), add_cv(cv, !t));
};

namespace detail
{
struct any_iterator_cant_copy_construct
{
    constexpr any_iterator_cant_copy_construct(auto&&) noexcept
    {}
};

PP_CIA remove_cvref_if_constructible = [](concepts::type auto&& t)
{
    constexpr auto T = PP_CT(t);

    if constexpr (is_constructible_pack(remove_cvref(T), T))
        return remove_cvref(T);
    else
        return type<detail::any_iterator_cant_copy_construct>;
};

template <typename T, typename U>
concept at_least_type = -type<T> >= -type<U>;

template <typename T>
using any_iterator_const_type =
    apply_transform_t<add_cv_reference * value<cv_qualifier::Const>, T>;

template <typename T>
using any_iterator_value_type =
    apply_transform_t<remove_cvref_if_constructible, T>;
}

///
/// @brief Base interface for any_iterator.
///
/// @tparam Category The iterator category.
/// @tparam T The result of dereferencing.
///
template <iterator_category Category, typename T>
class any_iterator_base
{};

template <iterator_category Category, typename T>
using any_iterator_unique_pointer =
    unique_pointer<pointer_new<any_iterator_base<Category, T>>>;

using any_iterator_unique_pointer_type = unique_tag_new_t;

///
/// @brief Base interface for any_iterator extended with copying functions.
///
/// @tparam Category The iterator category.
/// @tparam T The result of dereferencing.
///
template <iterator_category Category, typename T>
class any_iterator_base_base : public any_iterator_base<-Category, T>
{
    using CategoryT = value_t<Category>;
    using CategoryTPrev = value_t<-Category>;

public:
    ///
    /// @brief Creates copy of this iterator
    /// with the same type of dereferencing.
    ///
    /// @return A unique pointer to the new iterator.
    ///
    constexpr virtual any_iterator_unique_pointer<Category, T> copy(
        CategoryT) const = 0;

    ///
    /// @brief Creates copy of this iterator
    /// with added const to the referenced type of the type of
    /// dereferencing.
    ///
    /// @return A unique pointer to the new iterator.
    ///
    constexpr virtual any_iterator_unique_pointer<
        Category,
        detail::any_iterator_const_type<T>>
        copy_const(CategoryT) const = 0;

    ///
    /// @brief Creates copy of this iterator with value type as the type of
    /// dereferencing.
    ///
    /// @return A unique pointer to the new iterator.
    ///
    constexpr virtual any_iterator_unique_pointer<
        Category,
        detail::any_iterator_value_type<T>>
        copy_value(CategoryT) const = 0;

    ///
    /// @see any_iterator_base_base::copy
    ///
    constexpr any_iterator_unique_pointer<-Category, T> copy(
        CategoryTPrev) const override final
    {
        return copy(CategoryT{});
    }

    ///
    /// @see any_iterator_base_base::copy_const
    ///
    constexpr any_iterator_unique_pointer<-Category,
                                          detail::any_iterator_const_type<T>>
    copy_const(CategoryTPrev) const override final
    {
        return copy_const(CategoryT{});
    }

    ///
    /// @see any_iterator_base_base::copy_value
    ///
    constexpr any_iterator_unique_pointer<-Category,
                                          detail::any_iterator_value_type<T>>
    copy_value(CategoryTPrev) const override final
    {
        return copy_value(CategoryT{});
    }
};

/// @brief Base interface for any_iterator extended with copying functions.
/// Forward category.
///
/// @see PP::any_iterator_base_base
///
/// @tparam T The result of dereferencing.
///
template <typename T>
class any_iterator_base_base<iterator_category::fw, T>
{
    using Category = value_t<iterator_category::fw>;

public:
    ///
    /// @brief Gets the type of dereferencing of the iterator.
    ///
    /// @return The type of dereferencing of the iterator.
    ///
    constexpr auto get_type() const noexcept
    {
        return type<T>;
    }

    ///
    /// @see any_iterator_base_base::copy
    ///
    constexpr virtual any_iterator_unique_pointer<iterator_category::fw, T>
        copy(Category) const = 0;

    ///
    /// @see any_iterator_base_base::copy_const
    ///
    constexpr virtual any_iterator_unique_pointer<
        iterator_category::fw,
        detail::any_iterator_const_type<T>>
        copy_const(Category) const = 0;

    ///
    /// @see any_iterator_base_base::copy_value
    ///
    constexpr virtual any_iterator_unique_pointer<
        iterator_category::fw,
        detail::any_iterator_value_type<T>>
        copy_value(Category) const = 0;
};

constexpr auto any_iterator_copy_as(const auto& any_it,
                                    concepts::value auto&& category,
                                    concepts::type auto&& t)
{
    constexpr auto from_t = PP_CT(any_it.get_type());

    const any_iterator_base_base<PP_GV(category), PP_GT(from_t)>& i = any_it;

    auto category_value_t = to_value_t(category);

    if constexpr (t == from_t)
        return i.copy(category_value_t);
    else if constexpr (t == ~from_t)
        return i.copy_value(category_value_t);
    else
        return i.copy_const(category_value_t);
}

///
/// @brief Base interface for any_iterator. Forward category.
///
/// @see PP::any_iterator_base
///
/// @tparam T The result of dereferencing.
///
template <typename T>
class any_iterator_base<iterator_category::fw, T>
    : public any_iterator_base_base<iterator_category::fw, T>
{
public:
    ///
    /// @brief Dereferences the iterator. Represents operator*.
    ///
    /// @return The dereferenced value.
    ///
    constexpr virtual T dereference() const = 0;

    ///
    /// @brief Increments the iterator. Represents operator++.
    ///
    constexpr virtual void increment() = 0;

    ///
    /// @brief Compares two iterators.
    ///
    /// @param other The other iterator to compare to.
    /// @return true Equal.
    /// @return false Not equal.
    ///
    constexpr virtual bool equal(const any_iterator_base& other) const = 0;

    constexpr virtual ~any_iterator_base()
    {}
};

///
/// @brief Base interface for any_iterator. Bidirectional category.
///
/// @see PP::any_iterator_base
///
/// @tparam T The result of dereferencing.
///
template <typename T>
class any_iterator_base<iterator_category::bi, T>
    : public any_iterator_base_base<iterator_category::bi, T>
{
public:
    ///
    /// @brief Decrements the iterator. Represents operator--.
    ///
    constexpr virtual void decrement() = 0;
};

///
/// @brief Base interface for any_iterator. Random access category.
///
/// @see PP::any_iterator_base
///
/// @tparam T The result of dereferencing.
///
template <typename T>
class any_iterator_base<iterator_category::ra, T>
    : public any_iterator_base_base<iterator_category::ra, T>
{
public:
    ///
    /// @brief Advaces the iterator.
    ///
    /// @param offset The offset to advace by.
    ///
    constexpr virtual void advance(ptrdiff_t offset) = 0;

    ///
    /// @brief Indexes the iterator. Represents operator [].
    ///
    /// @param offset Offset of the indexing.
    /// @return The dereferenced value at the index.
    ///
    constexpr virtual T index(ptrdiff_t offset) const = 0;

    ///
    /// @brief Calculates the distance between two iterators.
    ///
    /// @param other The iterator to calculate the distance to.
    /// @return The distance.
    /// @retval >0 If this iterator is further than @p other.
    ///
    constexpr virtual ptrdiff_t diff(const any_iterator_base& other) const = 0;
};

///
/// @brief Base class for @ref PP::any_iterator_wrapper holding the strongly
/// typed iterator.
///
/// @tparam The iterator type.
///
template <typename Iterator>
class any_iterator_wrap
{
protected:
    ///
    /// @brief The iterator object.
    ///
    Iterator i;

public:
    ///
    /// @brief Constructs the wrap.
    ///
    /// @param i Initializer.
    ///
    explicit constexpr any_iterator_wrap(
        concepts::same_except_cvref<Iterator> auto&& i)
        : i(PP_F(i))
    {}

    ///
    /// @brief Compares the inner iterator object to an iterator of any
    /// type.
    ///
    /// @param i_other The iterator to compare to.
    /// @return The result of calling operator ==.
    ///
    constexpr decltype(auto) equal_sentinel(const auto& i_other) const
    {
        return i_other == i;
    }

    ///
    /// @brief Calculates the distance between two iterators.
    ///
    /// @param i_other The iterator to calculate distance to.
    /// @return The result of calling operator -.
    ///
    constexpr decltype(auto) difference_sentinel(const auto& i_other) const
    {
        return i_other - i;
    }
};

// template <typename... OtherIterators>
// constexpr auto invoke_on_first_valid(auto&& f, auto def, const auto&
// other)
//{
//	auto ptrs = make_tuple(dynamic_cast<const
// any_iterator_wrap<OtherIterators>*>(&other)...); 	auto i =
// tuple::find_dynamic([](auto* p) { return p != nullptr; }, ptrs);
//
//	if (i != sizeof...(OtherIterators))
//		return variant_visit(PP_F(f), get__dynamic(i, ptrs));
//	else
//		return def;
//}

template <typename OtherIterator, typename... OtherIterators>
constexpr auto invoke_on_first_valid(auto&& f, auto def, const auto& other)
{
    auto ptr = dynamic_cast<const any_iterator_wrap<OtherIterator>*>(&other);

    if constexpr (sizeof...(OtherIterators) == 0)
        return def;
    else
    {
        if (ptr)
            return PP_F(f)(ptr);
        else
            return invoke_on_first_valid<OtherIterators...>(PP_F(f),
                                                            def,
                                                            other);
    }
}

///
/// @brief Implementation of @ref PP::any_iterator_base.
///
/// @tparam Category The iterator category of this implementation.
/// @tparam C The iterator category of the wrapped iterator.
/// @tparam T The type of dereferencing.
/// @tparam Iterator The wrapped iterator type.
/// @tparam CompatibleIterators A list of compatible iterator types. These
/// types are compatible for comparison and calculating distance
///
template <iterator_category Category,
          iterator_category C,
          typename T,
          typename Iterator,
          typename... CompatibleIterators>
class any_iterator_wrapper_implementation
{};

///
/// @brief Implementation of @ref PP::any_iterator_base_base.
///
/// @tparam CategoryT The iterator category of this implementation.
/// @tparam C The iterator category of the wrapped iterator.
/// @tparam T The type of dereferencing.
/// @tparam Iterator The wrapped iterator type.
/// @tparam CompatibleIterators A list of compatible iterator types. These
/// types are compatible for comparison and calculating distance
///
template <typename CategoryT,
          typename CT,
          typename T,
          typename Iterator,
          typename... CompatibleIterators>
class any_iterator_wrapper
    : public any_iterator_wrapper_implementation<-type<CategoryT>,
                                                 -type<CT>,
                                                 T,
                                                 Iterator,
                                                 CompatibleIterators...>
{
    static constexpr auto Category = -type<CategoryT>;
    static constexpr auto C = -type<CT>;

    constexpr auto copy(concepts::value auto&& category,
                        concepts::type auto&& t) const
    {
        return make_unique_pointer(
            any_iterator_unique_pointer_type{},
            type<any_iterator_wrapper<value_t<PP_GV(category)>,
                                      CT,
                                      PP_GT(t),
                                      Iterator,
                                      CompatibleIterators...>>,
            this->i);
    }

public:
    using any_iterator_wrapper_implementation<
        Category,
        C,
        T,
        Iterator,
        CompatibleIterators...>::any_iterator_wrapper_implementation;

    ///
    /// @see any_iterator_base_base::copy
    ///
    constexpr any_iterator_unique_pointer<Category, T> copy(
        CategoryT c) const override final
    {
        return copy(c, type<T>);
    }

    ///
    /// @see any_iterator_base_base::copy_const
    ///
    constexpr any_iterator_unique_pointer<Category,
                                          detail::any_iterator_const_type<T>>
    copy_const(CategoryT c) const override final
    {
        return copy(c, type<detail::any_iterator_const_type<T>>);
    }

    ///
    /// @see any_iterator_base_base::copy_value
    ///
    constexpr any_iterator_unique_pointer<Category,
                                          detail::any_iterator_value_type<T>>
    copy_value(CategoryT c) const override final
    {
        return copy(c, type<detail::any_iterator_value_type<T>>);
    }
};

///
/// @brief Implementation of @ref PP::any_iterator_base. Forward category.
///
/// @see PP::any_iterator_wrapper_implementation.
///
/// @tparam C The iterator category of the wrapped iterator.
/// @tparam T The type of dereferencing.
/// @tparam Iterator The wrapped iterator type.
/// @tparam CompatibleIterators A list of compatible iterator types. These
/// types are compatible for comparison and calculating distance
///
template <iterator_category C,
          typename T,
          typename Iterator,
          typename... CompatibleIterators>
class any_iterator_wrapper_implementation<iterator_category::fw,
                                          C,
                                          T,
                                          Iterator,
                                          CompatibleIterators...>
    : public any_iterator_base<C, T>
    , public any_iterator_wrap<Iterator>
{
public:
    using any_iterator_wrap<Iterator>::any_iterator_wrap;

    ///
    /// @see any_iterator_base<iterator_category::fw, T>::dereference.
    ///
    constexpr T dereference() const override final
    {
        return *(this->i);
    }

    ///
    /// @see any_iterator_base<iterator_category::fw, T>::increment.
    ///
    constexpr void increment() override final
    {
        ++(this->i);
    }

    ///
    /// @see any_iterator_base<iterator_category::fw, T>::equal.
    ///
    constexpr bool equal(const any_iterator_base<iterator_category::fw, T>&
                             other) const override final
    {
        return invoke_on_first_valid<Iterator, CompatibleIterators...>(
            [this](auto* ptr)
            {
                return ptr->equal_sentinel(this->i);
            },
            false,
            other);
    }
};

///
/// @brief Implementation of @ref PP::any_iterator_base. Bidirectional
/// category.
///
/// @see PP::any_iterator_wrapper_implementation.
///
/// @tparam C The iterator category of the wrapped iterator.
/// @tparam T The type of dereferencing.
/// @tparam Iterator The wrapped iterator type.
/// @tparam CompatibleIterators A list of compatible iterator types. These
/// types are compatible for comparison and calculating distance
///
template <iterator_category C,
          typename T,
          typename Iterator,
          typename... CompatibleIterators>
class any_iterator_wrapper_implementation<iterator_category::bi,
                                          C,
                                          T,
                                          Iterator,
                                          CompatibleIterators...>
    : public any_iterator_wrapper_implementation<iterator_category::fw,
                                                 C,
                                                 T,
                                                 Iterator,
                                                 CompatibleIterators...>
{
public:
    using any_iterator_wrapper_implementation<
        iterator_category::fw,
        C,
        T,
        Iterator,
        CompatibleIterators...>::any_iterator_wrapper_implementation;

    ///
    /// @see any_iterator_base<iterator_category::bi, T>::decrement.
    ///
    constexpr void decrement() override final
    {
        --this->i;
    }
};

///
/// @brief Implementation of @ref PP::any_iterator_base. Random access
/// category.
///
/// @see PP::any_iterator_wrapper_implementation.
///
/// @tparam C The iterator category of the wrapped iterator.
/// @tparam T The type of dereferencing.
/// @tparam Iterator The wrapped iterator type.
/// @tparam CompatibleIterators A list of compatible iterator types. These
/// types are compatible for comparison and calculating distance
///
template <iterator_category C,
          typename T,
          typename Iterator,
          typename... CompatibleIterators>
class any_iterator_wrapper_implementation<iterator_category::ra,
                                          C,
                                          T,
                                          Iterator,
                                          CompatibleIterators...>
    : public any_iterator_wrapper_implementation<iterator_category::bi,
                                                 C,
                                                 T,
                                                 Iterator,
                                                 CompatibleIterators...>
{
public:
    using any_iterator_wrapper_implementation<
        iterator_category::bi,
        C,
        T,
        Iterator,
        CompatibleIterators...>::any_iterator_wrapper_implementation;

    ///
    /// @see any_iterator_base<iterator_category::ra, T>::advance.
    ///
    constexpr void advance(ptrdiff_t offset) override final
    {
        this->i += offset;
    }

    ///
    /// @see any_iterator_base<iterator_category::ra, T>::index.
    ///
    constexpr T index(ptrdiff_t offset) const override final
    {
        return this->i[offset];
    }

    ///
    /// @see any_iterator_base<iterator_category::ra, T>::diff.
    ///
    constexpr ptrdiff_t diff(const any_iterator_base<iterator_category::ra, T>&
                                 other) const override final
    {
        return invoke_on_first_valid<Iterator, CompatibleIterators...>(
            [this](auto* ptr)
            {
                return ptr->difference_sentinel(this->i);
            },
            (ptrdiff_t)-42,
            other);
    }
};

///
/// @brief A type erased iterator.
///
/// @tparam Category The iterator category of the implementation.
/// @tparam C The iterator category of the iterator.
/// @tparam T The type of dereferencing.
///
template <typename Category, typename C, typename T>
class any_iterator_implementation
{};

///
/// @brief The any_iterator implementation class. Forward category.
///
/// @see PP::any_iterator_implementation.
///
/// @tparam C The iterator category of the iterator.
/// @tparam T The type of dereferencing.
///
template <typename C, typename T>
class any_iterator_implementation<value_t<iterator_category::fw>, C, T>
{
    template <typename, typename, typename>
    friend class any_iterator_implementation;

    using pointer_type = any_iterator_unique_pointer<-type<C>, T>;

protected:
    ///
    /// @brief A @ref PP::unique_pointer to a wrapped iterator.
    ///
    pointer_type p;

public:
    ///
    /// @brief Constructs the any_iterator with a @ref PP::unique_pointer to
    /// a wrapped iterator.
    ///
    /// @param p A reference to the pointer.
    ///
    constexpr any_iterator_implementation(placeholder_t, auto&& p)
        : p(move(p))
    {}

    ///
    /// @brief Copy constructor.
    ///
    /// @param other A reference to the object to copy.
    ///
    constexpr any_iterator_implementation(
        const any_iterator_implementation& other) noexcept
        : any_iterator_implementation(
              placeholder,
              any_iterator_copy_as(*other.p,
                                   value<iterator_category::fw>,
                                   type<T>))
    {}

    ///
    /// @brief Move constructor.
    ///
    /// @param other A reference to the object to move.
    ///
    constexpr any_iterator_implementation(
        any_iterator_implementation&& other) noexcept
        : any_iterator_implementation(placeholder, move(other.p))
    {}

    ///
    /// @brief Copy constructor from any_iterator with a different category.
    ///
    /// @param other A reference to the object to copy.
    ///
    template <detail::at_least_type<C> COther, concepts::convertible_to<T> U>
    constexpr any_iterator_implementation(
        const any_iterator_implementation<value_t<iterator_category::fw>,
                                          COther,
                                          U>& other) noexcept
        : any_iterator_implementation(
              placeholder,
              any_iterator_copy_as(*other.p,
                                   value<iterator_category::fw>,
                                   type<T>))
    {}

    ///
    /// @brief Move constructor from any_iterator with a different category.
    ///
    /// @param other A reference to the object to move.
    ///
    template <detail::at_least_type<C> COther>
    constexpr any_iterator_implementation(
        any_iterator_implementation<value_t<iterator_category::fw>, COther, T>&&
            other) noexcept
        : any_iterator_implementation(placeholder, move(other.p))
    {}

    ///
    /// @brief Dereferences the iterator.
    ///
    /// @return The dereferenced value.
    ///
    constexpr decltype(auto) operator*() const
    {
        return p->dereference();
    }

    ///
    /// @brief Dereferences, but acts as a pointer to the dereferenced
    /// value.
    ///
    /// @return An @ref PP::arrow_operator_wrapper.
    ///
    constexpr auto operator->() const
    {
        return make_arrow_operator_wrapper(
            [this]()
            {
                return **this;
            });
    }

    ///
    /// @brief Increments the pointer.
    ///
    constexpr void step()
    {
        p->increment();
    }

    ///
    /// @brief Compares with iterator of any type.
    ///
    /// @param other Iterator to compare to.
    /// @return true Equal.
    /// @return false Not equal.
    ///
    constexpr bool operator==(const auto& other) const
    {
        return (!p && !other.p) || (p && other.p && p->equal(*other.p));
    }
};

///
/// @brief The any_iterator implementation class. Bidirectional category.
///
/// @see PP::any_iterator_implementation.
///
/// @tparam C The iterator category of the iterator.
/// @tparam T The type of dereferencing.
///
template <typename C, typename T>
class any_iterator_implementation<value_t<iterator_category::bi>, C, T>
    : public any_iterator_implementation<value_t<iterator_category::fw>, C, T>
{
    template <typename, typename, typename>
    friend class any_iterator_implementation;

public:
    ///
    /// @brief Constructs the any_iterator with a @ref PP::unique_pointer to
    /// a wrapped iterator.
    ///
    /// @param p A reference to the pointer.
    ///
    constexpr any_iterator_implementation(placeholder_t, auto&& p)
        : any_iterator_implementation<value_t<iterator_category::fw>, C, T>(
              placeholder,
              move(p))
    {}

    ///
    /// @brief Copy constructor.
    ///
    /// @param other A reference to the object to copy.
    ///
    constexpr any_iterator_implementation(
        const any_iterator_implementation& other) noexcept
        : any_iterator_implementation(
              placeholder,
              other.p->copy(value<iterator_category::bi>))
    {}
    ///
    /// @brief Move constructor.
    ///
    /// @param other A reference to the object to move.
    ///
    constexpr any_iterator_implementation(
        any_iterator_implementation&& other) noexcept
        : any_iterator_implementation<value_t<iterator_category::fw>, C, T>(
              move(other))
    {}

    ///
    /// @brief Copy constructor from any_iterator with a different category.
    ///
    /// @param other A reference to the object to copy.
    ///
    template <detail::at_least_type<C> COther, concepts::convertible_to<T> U>
    constexpr any_iterator_implementation(
        const any_iterator_implementation<value_t<iterator_category::fw>,
                                          COther,
                                          U>& other) noexcept
        : any_iterator_implementation(
              placeholder,
              any_iterator_copy_as(*other.p,
                                   value<iterator_category::bi>,
                                   type<T>))
    {}

    ///
    /// @brief Move constructor from any_iterator with a different category.
    ///
    /// @param other A reference to the object to move.
    ///
    template <detail::at_least_type<C> COther>
    constexpr any_iterator_implementation(
        any_iterator_implementation<value_t<iterator_category::fw>, COther, T>&&
            other) noexcept
        : any_iterator_implementation<value_t<iterator_category::fw>, C, T>(
              move(other))
    {}

    ///
    /// @brief Decrements the iterator.
    ///
    constexpr void step_back()
    {
        this->p->decrement();
    }
};

///
/// @brief The any_iterator implementation class. Random access category.
///
/// @see PP::any_iterator_implementation.
///
/// @tparam C The iterator category of the iterator.
/// @tparam T The type of dereferencing.
///
template <typename C, typename T>
class any_iterator_implementation<value_t<iterator_category::ra>, C, T>
    : public any_iterator_implementation<value_t<iterator_category::bi>, C, T>
{
    template <typename, typename, typename>
    friend class any_iterator_implementation;

public:
    ///
    /// @brief Constructs the any_iterator with a @ref PP::unique_pointer to
    /// a wrapped iterator.
    ///
    /// @param p A reference to the pointer.
    ///
    constexpr any_iterator_implementation(placeholder_t, auto&& p)
        : any_iterator_implementation<value_t<iterator_category::bi>, C, T>(
              placeholder,
              move(p))
    {}

    ///
    /// @brief Copy constructor.
    ///
    /// @param other A reference to the object to copy.
    ///
    constexpr any_iterator_implementation(
        const any_iterator_implementation& other) noexcept
        : any_iterator_implementation(
              placeholder,
              other.p->copy(value<iterator_category::ra>))
    {}

    ///
    /// @brief Move constructor .
    ///
    /// @param other A reference to the object to move.
    ///
    constexpr any_iterator_implementation(
        any_iterator_implementation&& other) noexcept
        : any_iterator_implementation<value_t<iterator_category::bi>, C, T>(
              move(other))
    {}

    ///
    /// @brief Copy constructor from any_iterator with different category.
    ///
    /// @param other A reference to the object to copy.
    ///
    template <detail::at_least_type<C> COther, concepts::convertible_to<T> U>
    constexpr any_iterator_implementation(
        const any_iterator_implementation<value_t<iterator_category::fw>,
                                          COther,
                                          U>& other) noexcept
        : any_iterator_implementation(
              placeholder,
              any_iterator_copy_as(*other.p,
                                   value<iterator_category::ra>,
                                   type<T>))
    {}

    ///
    /// @brief Move constructor from any_iterator with different category.
    ///
    /// @param other A reference to the object to move.
    ///
    template <detail::at_least_type<C> COther>
    constexpr any_iterator_implementation(
        any_iterator_implementation<value_t<iterator_category::fw>, COther, T>&&
            other) noexcept
        : any_iterator_implementation<value_t<iterator_category::bi>, C, T>(
              move(other))
    {}

    ///
    /// @brief Calculates the distance between two iterators.
    ///
    /// @param other The iterator to calculate distance to.
    ///
    constexpr decltype(auto) operator-(
        const any_iterator_implementation<value_t<iterator_category::fw>, C, T>&
            other) const
    {
        return this->p->diff(*other.p);
    }

    ///
    /// @brief Advances the iterator.
    ///
    /// @param offset The offset to advance by.
    ///
    constexpr void advance(ptrdiff_t offset)
    {
        this->p->advance(offset);
    }

    ///
    /// @brief Indexes the iterator.
    ///
    /// @param offset The index.
    /// @return The dereferenced value.
    ///
    constexpr decltype(auto) operator[](ptrdiff_t offset) const
    {
        return this->p->index(offset);
    }
};

namespace detail
{
constexpr auto get_iterator_category_value_t(concepts::type auto&& i)
{
    constexpr auto I = PP_CT(i);

    if constexpr (is_iterator_ra(I))
        return value<iterator_category::ra>;
    else if constexpr (is_iterator_bi(I))
        return value<iterator_category::bi>;
    else
        return value<iterator_category::fw>;
}

constexpr auto make_any_iterator_implementation_type(
    concepts::value auto&& category,
    concepts::type auto&& dereference_type)
{
    auto category_type = PP_DT(to_value_t(category));

    return Template<any_iterator_implementation>(category_type,
                                                 category_type,
                                                 dereference_type);
}
constexpr auto make_any_iterator_wrapper_type(
    concepts::value auto&& category,
    concepts::type auto&& dereference_type,
    concepts::type auto&& iterator_type,
    concepts::tuple auto compatible_iterators)
{
    auto category_type = PP_DT(to_value_t(category));

    return Template<any_iterator_wrapper>[category_type += category_type +=
                                          dereference_type += iterator_type +=
                                          compatible_iterators];
}

constexpr auto make_any_iterator_pointer(
    concepts::iterator auto i,
    concepts::type auto&& dereference_type,
    concepts::tuple auto compatible_iterators)
{
    auto iterator_type = PP_DT(i);

    return make_unique_pointer(any_iterator_unique_pointer_type{},
                               make_any_iterator_wrapper_type(
                                   get_iterator_category_value_t(iterator_type),
                                   dereference_type,
                                   iterator_type,
                                   compatible_iterators),
                               move(i));
}
constexpr auto make_any_iterator(concepts::iterator auto i,
                                 concepts::tuple auto compatible_iterators)
{
    auto iterator_type = PP_DT(i);
    auto dereference_type = PP_DT(*i);
    auto category = get_iterator_category_value_t(iterator_type);

    return make_any_iterator_implementation_type(category, dereference_type)(
        placeholder,
        make_any_iterator_pointer(i, dereference_type, compatible_iterators));
}
}

PP_CIA make_any_iterator = overloaded(
    [](concepts::iterator auto i, concepts::tuple auto compatible_iterators)
    {
        return detail::make_any_iterator(i, compatible_iterators);
    },
    [](concepts::iterator auto i)
    {
        return detail::make_any_iterator(i, tuple_empty{});
    });

template <iterator_category Category, typename T>
using any_iterator = PP_GT(
    detail::make_any_iterator_implementation_type(value<Category>, type<T>));
}
