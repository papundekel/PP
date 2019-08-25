#pragma once 
#include "number.hpp"
#include "pointer_type.hpp"
#include "character.hpp"
#include "floating.hpp"
#include "fundamental_integers.hpp"
#include "fundamental_floats.hpp"
#include "fundamental_chars.hpp"

using fundamental_types = pack<void, nullptr_t, bool>
::append<fundamental_integers>
::append<fundamental_floats>
::append<fundamental_chars>;

template <typename T>
using fundamental = value_t<pointer_type<T>::v || fundamental_types::contains<same<T>::as>>;