#pragma once
#include <cstddef>
#include <array>
#include <algorithm>

#include "add_pointer.hpp"
#include "concepts/convertible_to.hpp"
#include "decompose_template.hpp"
#include "functional/comparisons.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "placeholder.hpp"
#include "remove_cvref.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, typename S, typename A>
		class pointer_stack;

		namespace detail
		{
			static constexpr bool pointer_stack_compatible(auto from, auto to) noexcept
			{
				if (from->Template == to->Template == template_v<pointer_stack>)
				{
					auto [value_types, sizes, alignments] = tuple_zip(std::pair{ from->types, to->types });

					return is_convertible_to[add_pointer * value_types]
						&& less_or_eq[sizes]
						&& less_or_eq[alignments];
				}

				return false;
			}
		}

		template <typename T, typename S, typename A>
		class pointer_stack
		{
		public:
			static constexpr std::size_t Size = S::value_f();
			static constexpr std::size_t Alignment = A::value_f();

		private:
			template <typename U, typename SOther, typename AOther>
			friend class pointer_stack;

			alignas(Alignment) std::array<std::byte, Size> buffer;
			bool is_valid_;

			constexpr void* get_raw_ptr() const noexcept
			{
				return const_cast<std::byte*>(buffer.data());
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

			constexpr pointer_stack(auto type, auto&&... args) // TODO noexcept(?)
				: buffer()
				, is_valid_(true)
			{
				new (get_raw_ptr()) PP_GET_TYPE(type)(PP_FORWARD(args)...);
			}

			constexpr pointer_stack(placeholder_t, auto&& value)
				: pointer_stack(~PP_DECLTYPE(value), PP_FORWARD(value))
			{}

			constexpr pointer_stack(const auto& other) noexcept
				requires (pointer_stack_compatible(type_v<pointer_stack>, PP_DECLTYPE(other)))
			{
				std::copy(other.buffer.begin(), other.buffer.end(), buffer.begin());
				is_valid_ = other.is_valid_;
			}

			constexpr T* get_ptr() const noexcept
			{
				if (is_valid())
					return reinterpret_cast<T*>(get_raw_ptr());
				else
					return nullptr;
			}

			constexpr void destroy() const
			{
				if (auto ptr = get_ptr(); ptr)
					ptr->~T();
			}
		};

		template <typename T, typename... Args>
		pointer_stack(PP::type_t<T>, Args&&...) -> pointer_stack<T, value_t<sizeof(T)>, value_t<alignof(T)>>;
		template <typename T>
		pointer_stack(PP::placeholder_t, T&&) -> pointer_stack<T, value_t<sizeof(T)>, value_t<alignof(T)>>;
	}

	template <typename T, std::size_t Size, std::size_t Alignment>
	using pointer_stack = detail::pointer_stack<T, value_t<Size>, value_t<Alignment>>;
}
