#pragma once
#include "apply_template.hpp"
#include "apply_transform.hpp"
#include "arrow_operator_wrapper.hpp"
#include "concepts/pointer.hpp"
#include "decompose_template.hpp"
#include "get_type.hpp"
#include "iterator_inner.hpp"
#include "remove_cvref.hpp"
#include "simple_view.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		struct transform_iterator_pointer_base
		{
			T ptr;
		};

		constexpr auto&& transform_iterator_base_get(auto&& i) noexcept
		{
			if constexpr (PP_DECLTYPE(i)->Template == template_v<transform_iterator_pointer_base>)
				return i.ptr;
			else
				return PP_FORWARD(i);
		}

		constexpr inline auto x = [](type_wrap auto t)
		{
			if constexpr (is_pointer(PP_COPY_TYPE(t)))
				return template_v<transform_iterator_pointer_base>[t];
			else
				return t;
		};

		template <typename Transform>
		using transform_iterator_base_t = apply_transform_t<x, Transform>;
	}

	template <typename BaseIterator, typename Transform>
	class transform_iterator
	{
		BaseIterator i;
		Transform t;

	public:
		constexpr transform_iterator(BaseIterator i, Transform t)
			: i(std::move(i))
			, t(std::move(t))
		{}

		constexpr decltype(auto) operator*() const
		{
			return t(*i);
		}
		constexpr auto operator->() const
		{
			return arrow_operator_wrapper(**this);
		}
		constexpr auto operator+(size_t offset)
		{
			return transform_iterator(i + offset, t);
		}
		constexpr auto operator==(concepts::iterator auto other) const
		{
			return i == PP::iterator_base(other);
		}
		constexpr auto operator-(concepts::iterator auto other) const
		{
			return i - PP::iterator_base(other);
		}
		constexpr decltype(auto) operator[](std::size_t index) const
		{
			return t(i[index]);
		}
		constexpr BaseIterator inner() const
		{
			return i;
		}
	};

	template <typename Functor>
	struct transform
	{
		Functor functor;
	};

	constexpr auto transform_view(concepts::view auto&& v, auto&& f)
	{
		return
			transform_iterator(begin(PP_FORWARD(v)), PP_FORWARD(f))	^
			transform_iterator(  end(PP_FORWARD(v)), PP_FORWARD(f));
	}

	constexpr auto operator&(concepts::iterator auto i, transform<auto> t)
	{
		return transform_iterator(i, std::move(t).functor);
	}

	constexpr auto operator||(concepts::view auto&& v, transform<auto> t)
	{
		return begin(PP_FORWARD(v)) & std::move(t) ^ end(PP_FORWARD(v));
	}

	constexpr auto operator|(concepts::view auto&& v, transform<auto> t)
	{
		return transform_view(PP_FORWARD(v), std::move(t).functor);
	}
}
