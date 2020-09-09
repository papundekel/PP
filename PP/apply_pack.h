#pragma once
#include "value_t.h"
#include "type_pack.h"
#include "get_value.h"
#include "get_type.h"
#include "extract_value.h"
#include "extract_type.h"
namespace PP
{

}
namespace detail
{
	struct apply_pack__isnt_pack_error {};

	template <template <typename...> typename, typename>
	struct apply_pack_helper : value_t<apply_pack__isnt_pack_error{}>
	{};
	template <template <typename...> typename A, typename... T>
	struct apply_pack_helper<A, type_pack<T...>> : extract_value<A<T...>>
	{};

	template <template <typename...> typename, typename>
	struct apply_pack_types_helper : type_t<detail::apply_pack__isnt_pack_error>
	{};
	template <template <typename...> typename A, typename... T>
	struct apply_pack_types_helper<A, type_pack<T...>> : extract_type<A<T...>>
	{};
}

template <template <typename...> typename A, typename Pack>
using apply_pack = detail::apply_pack_helper<A, get_type<Pack>>;

template <template <typename...> typename A, typename Pack>
using apply_pack_types = detail::apply_pack_types_helper<A, get_type<Pack>>;
