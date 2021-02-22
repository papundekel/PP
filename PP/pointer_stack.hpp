#pragma once

#include "add_pointer.hpp"
#include "alignment_of.hpp"
#include "array.hpp"
#include "concepts/convertible_to.hpp"
#include "construct_at_pack.hpp"
#include "decompose_template.hpp"
#include "functional/operators.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "placeholder.hpp"
#include "remove_cvref.hpp"
#include "size_of.hpp"
#include "tuple_zip_with.hpp"
#include "view_copy.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, typename S, typename A>
		class pointer_stack;

		template <typename F, typename T>
		concept pointer_stack_compatible = [](concepts::type auto from, concepts::type auto to) noexcept
		{
			constexpr auto From = PP_COPY_TYPE(from);
			constexpr auto   To = PP_COPY_TYPE(to);

			if constexpr (From->Template == To->Template && From->Template == Template<pointer_stack>)
			{
				auto [value_types, sizes, alignments] = !tuple_zip(make_tuple(From->types, To->types));

				return is_convertible_to[add_pointer + value_types]
					&& lte[sizes]
					&& lte[alignments];
			}
			else
				return false;
		}(type<F>, type<T>);

		template <typename T, typename S, typename A>
		class pointer_stack
		{
		private:
			template <typename, typename, typename>
			friend class pointer_stack;

			alignas(-type<A>) PP::detail::array<char, S> buffer;
			bool is_valid_;

			constexpr T* get_ptr_impl() const noexcept
			{
				return reinterpret_cast<T*>(const_cast<char*>(buffer.data()));
			}

			constexpr bool is_valid() const noexcept
			{
				return is_valid_;
			}

		public:
			constexpr pointer_stack() noexcept
				: buffer()
				, is_valid_(false)
			{}

			constexpr pointer_stack(placeholder_t, auto&&... args)
				: buffer()
				, is_valid_(true)
			{
				construct_at_pack(get_ptr_impl(), PP_FORWARD(args)...);
			}

			constexpr pointer_stack(const pointer_stack_compatible<pointer_stack> auto& other) noexcept
			{
				view_copy(buffer, other.buffer);
				is_valid_ = other.is_valid_;
			}

			constexpr T* get_ptr() const noexcept
			{
				return is_valid() ? get_ptr_impl() : nullptr;
			}

			constexpr void deallocate() const
			{
				if (auto ptr = get_ptr(); ptr)
					ptr->~T();
			}
		};
	}

	template <typename T, size_t Size, size_t Alignment>
	using pointer_stack = detail::pointer_stack<T, value_t<Size>, value_t<Alignment>>;

	PP_FUNCTOR(make_pointer_stack, concepts::type auto t, auto&&... args)
	{
		constexpr auto T = PP_COPY_TYPE(t);

		return pointer_stack<PP_GET_TYPE(T), size_of(T), alignment_of(T)>(placeholder, PP_FORWARD(args)...);
	});
	PP_FUNCTOR(make_pointer_stack_copy, auto&& value)
	{
		return make_pointer_stack(~PP_DECLTYPE(value), PP_FORWARD(value));
	});
}
